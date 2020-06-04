
#include <iostream>
#include <vector>
#include <list>
#include <String>
#include <sstream>
using namespace std;
class customer{
public:
	int arrival;
	int service;
	int tolerant;
	customer operator= (customer  c1)
	{
		customer c;
		c.arrival=c1.arrival;
		c.service=c1.service;
		c.tolerant=c1.tolerant;
	    return c;
	}
};
class window: public customer{
public:
	int served;
	bool busy;
};
int free_window(vector <window> w);
void check_violation(list <customer>  & q, int const time){
	for (list<customer>::iterator i=q.begin(); i!=q.end(); i++) {
		if((*i).arrival > time)
		{
			q.erase(i);
			cout<<"Time="<<time<<"\tCustomer who arrived"<<(*i).arrival<<"was left the queue"<<endl;
		}
	}
}
void check_served(vector <window> & w, int const time){
	for (int i = 0; i < w.size(); ++i) {
		if(w[i].busy && w[i].service>0)
			w[i].service--;
		else if(w[i].busy &&  w[i].service==0)
		{
			w[i].busy=0;
			w[i].arrival=-1;
			w[i].service=-1;
			w[i].tolerant=-1;
			w[i].served++;
			cout<<"Time= "<<time<<"\tCustomer who arrived at "<<w[i].arrival<<"is finished"<<endl;
			cout<<"Time= "<<time<<"\tWindow "<<i<<"is free"<<endl;
		}

	}
}
int s2i(string s){
	stringstream datastr;
	int x;
	datastr.str(s);
	datastr >> x;
	return x;
}
vector <int> Func1(list<string> input, int Y, int Z)
{
	bool initial=1;
	list <customer> q;
	vector <window> wind;
	//vector <int> event;
	int time=0;
	customer c;

	window w;
	for (int i = 0; i < Z; ++i) {
		w.busy=0;
		w.arrival=-1;
		w.service=-1;
		w.tolerant=-1;
		w.served=0;
		wind.push_back(w);
	}

	int data;
	bool cust_inter=0;
	while(input.size()>0)
	{
		c.arrival=s2i(input.front());
		if(initial)
		{
			input.pop_front();
			time=c.arrival;
			c.service=s2i(input.front());
			input.pop_front();
			c.tolerant=s2i(input.front());
			input.pop_front();
			if(q.size()<=Y && c.tolerant>time)
			{
				cout<<c.arrival<<endl;
				cout<<q.size()<<endl;
				q.push_back(c);
				cout<<q.size()<<endl;
				cout<<q.back().arrival;
			}
			cust_inter=1;
		}
		else if(c.arrival==time)
		{
			input.pop_front();
			c.service=s2i(input.front());
			input.pop_front();
			c.tolerant=s2i(input.front());
			input.pop_front();
			if(q.size()<=Y && c.tolerant>time)
				q.push_back(c);
			cust_inter=1;
			c.arrival=-1;
			c.service=-1;
			c.tolerant=-1;
		}
		if(cust_inter)
		{
			int f=free_window(wind);
			if(f!=-1 && q.size()>0)
			{
				list<customer>::iterator p = q.begin();
				cout<<p->arrival;
				cout<<p->service;
				c=q.front();
				q.pop_front();
				wind[f].arrival=c.arrival;
				wind[f].service=c.service;
				wind[f].tolerant=c.tolerant;
				wind[f].busy=1;
				cout<<"Window"<<f<<"is busy now"<<endl;

			}
		}
		if(!initial)
		{
			check_violation(q, time);
			check_served(wind, time);
		}
		else
			initial=0;
		time++;
		cust_inter=0;
	}
}
int free_window(vector <window> w){
	for (int i = 0; i <w.size() ; ++i) {
		if(w[i].busy==0)
			return i;
	return -1;
	}
}
int main() {

	vector<int> a;
	list <string> cust;
	cust.push_back("10");
	cust.push_back("3");
	cust.push_back("20");

	cust.push_back("23");
	cust.push_back("5");
	cust.push_back("33");

	cust.push_back("25");
	cust.push_back("10");
	cust.push_back("30");

	int y=10;
	int z=10;
	a=Func1(cust, y, z);
	return 0;
}
