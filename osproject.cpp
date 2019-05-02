/* write to me at saurabhdubey097@gmail.com */
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <bits/stdc++.h>
#include<conio.h>
using namespace std;

struct Data_Working
{
	int Num;
	int Process_ID;  
	int timeofA; 
	int timeofB; 
	int pp; 
	int finishtym; 
	int remaining_tym; 
	int waiting_time; 
	int start_time; 
	int rest_time;

};

struct Data_Working current;
typedef struct Data_Working P_d ;

bool idsort(const P_d& x , const P_d& y)
{
	return x.Process_ID < y.Process_ID;
}

bool arrivalsort( const P_d& x ,const P_d& y)
{
	if(x.timeofA < y.timeofA)
		return true;
	else if(x.timeofA > y.timeofA)
		return false;
	if(x.pp < y.pp)
		return true;
	else if(x.pp > y.pp)
		return false;
	if(x.Process_ID < y.Process_ID)
		return true;

	return false;
}


bool Numsort( const P_d& x ,const P_d& y)
{
	return x.Num < y.Num;
}

struct comPare
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.pp > y.pp )
			return true;
		else if( x.pp < y.pp )
			return false;
		if( x.Process_ID > y.Process_ID )
			return true;

		return false;
		
	}
	
};


void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" PROCESS id :"<<mv[i].Process_ID<<" _time : "<<mv[i].timeofA<<" timeofB : "<<mv[i].timeofB<<" pp : "<<mv[i].pp<<endl;
	}

}

int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0; 
	int rq_process = 0; 
	int timeofA;
	int timeofB;
	int Process_ID;
	int pp;
	int n;
	int clock;
	int total_exection_time = 0;
	system("Color B5");
	cout<<"Enter Number of processes: \n";
	cin>>n;
	for( i= 0; i< n; i++ )
	
	{  system("Color 0C");
	 cout<<"Enter the process id,Arrival time, Burst time and priority:\n";
	    
		cin>>Process_ID>>timeofA>>timeofB>>pp;
		temp.Num = i+1;
		temp.timeofA = timeofA;
		temp.timeofB = timeofB;
		temp.remaining_tym = timeofB;
		temp.Process_ID = Process_ID;
		temp.pp = pp;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );
    
    total_exection_time = total_exection_time + input[0].timeofA;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_exection_time >= input[i].timeofA )
    	{
    		total_exection_time = total_exection_time +input[i].timeofB;
    	}
    	else
    	{
    		int diff = (input[i].timeofA - total_exection_time);
    		total_exection_time = total_exection_time + diff + timeofB;

    	}
    }

	int Ghant[total_exection_time]={0}; 
	for( i= 0; i< total_exection_time; i++ )
	{
		Ghant[i]=-1;
	}
	

	priority_queue < P_d ,vector<Data_Working> ,comPare> pq; 

	queue< P_d > rq;
	int cpu_state = 0; 
	int quantum = 4 ; 
	current.Process_ID= -2;
	current.pp = 999999;

	for ( clock = 0; clock< total_exection_time; clock++ )
	{
		
		for( int j = 0; j< n ; j++ )
		{
			if(clock == input[j].timeofA)
			{
				pq.push(input[j]);
			}
		}
		

		if(cpu_state == 0) 
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4; 
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1) //If cpu has any procss
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().pp < current.pp ) 
				{
					rq.push(current); 
					current = pq.top();
					pq.pop();
					quantum = 4; 
				}
			}
			else if(rq_process == 1 && (!pq.empty())) 
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}
			

		}


		if(current.Process_ID != -2) 
		{
			current.remaining_tym--;
			quantum--;
			Ghant[clock] = current.Process_ID;
			if(current.remaining_tym == 0) 
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.Process_ID = -2;
				current.pp = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 ) 
			{
				rq.push(current);
				current.Process_ID = -2;
				current.pp = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;

			}

		}
		
	}


	sort( input.begin(), input.end(), idsort );
	
	for(int i=0;i<n;i++)
	{
		for(int k=total_exection_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].finishtym=k+1;
				break;

			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_exection_time;k++)
		{

			if(Ghant[k]==i+1)
			{
				input[i].start_time=k;
				break;
			}
		}
	}
	
	sort( input.begin(), input.end(), Numsort );

	for(int i=0;i<n;i++)
	{
		input[i].rest_time=input[i].start_time-input[i].timeofA;
		input[i].waiting_time=(input[i].finishtym-input[i].timeofA)-input[i].timeofB;

	}
	
    //system("Color C1");

	 system("Color F2");
	 cout<<"::::Process_id Response_time Finish_time Waiting_Time ::::\n";
	for(int i=0;i<n;i++)
	{   cout<<"      ";
	system("Color 5A");
	cout<<input[i].Process_ID<<"         "<<input[i].rest_time<<"            "<<input[i].finishtym<<"             "<<input[i].waiting_time<<endl;
		
	}	
	return 0;
}
