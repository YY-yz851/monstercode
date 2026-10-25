#include<iostream>
#include<ctime>
#include<cmath>
#include<cstdlib>
using namespace std;
class Monster {
		int spieciesId,hp,level;
	public:
		Monster(int id=0,int h=0,int l=1): 
         spieciesId(id),hp(h),level(l){};	
		~Monster() {        }
		int power() {
            long long p;
            p=(long long)hp*level/10;
            return (int)p;
		}
		int getHp(){
			int h;
			h=hp;
			return h;	
		}
		int getLevel(){
			int l;
			l=level;
			return l;
		}
		int getSpeciesId(){
			int id=spieciesId;
			return id;	
		}
};
class Team{
	Monster*monsters;
	int capacity;
	int count;
public:
	friend class Trainer;
	Team(){
	 count=0; capacity=3;
	monsters=new Monster[capacity];	
	};
	~Team(){
	   	delete []monsters;
	   };
	Team (const Team& other){
		capacity=other.capacity;
		count=other.count;
		monsters=new Monster[capacity];
		for(int i=0;i<count;i++){
			monsters[i]=other.monsters[i];
		}
	}
	Team& operator=(const Team& other){
		if(this!=&other){
			delete[] monsters;
			capacity=other.capacity;
			count=other.count;
			monsters=new Monster[capacity];
		  for(int i=0;i<count;i++){
		  	monsters[i]=other.monsters[i];
		  }
		}
		return *this;
	}
	void add(const Monster&m){
		if(count==capacity){
			Monster*mon;
			capacity+=3;
			mon=new Monster[capacity];
			for(int i=0;i<count;i++){
				mon[i]=monsters[i];
			}
			delete []monsters;
			monsters=mon;
		}
		monsters[count++]=m;
			};
	void release(int index){
		if(index<0||index>=count){
			return;
		}
		else{
			monsters[index]=monsters[count-1];
			count--;
		}
	};
	int getCount()const{
		int cou=count;
	return cou;	
	}
	double getTotalPower(){
		if(monsters==NULL){
			return 0.0;
		}
		else{
			double total=0.0;
			for(int i=0;i<count;i++){
				total+=monsters[i].power();
			}
			return total;
		}
	}
	Monster get(int i)const{
    return monsters[i];
	}
		};
class Trainer{
	int trainerId;
	Team team;
public:
	friend class Team;
	Trainer(int id=0):trainerId(id){};	
	void catchMonster(int id,int hp,int level){
		Monster a(id,hp,level);
		team.add(a);
	};
	void releaseMonster(int index){
		team.release(index);
	};
	double getAveragePower(){
		double ave=0.0;
		if(team.getCount()==0){return 0.0;} 
		ave=(double)team.getTotalPower()/team.getCount();
	return 	ave;
	}
	Trainer(const Trainer&other){
		trainerId=other.trainerId;
		team=other.team;
		
	}
	Trainer& operator=(const Trainer& other){
		if(this!=&other){
	 	trainerId=other.trainerId; team=other.team;
	 }
	 return *this;
	};
	Trainer operator+(const Trainer& r)const{
		Trainer a(this->trainerId+r.trainerId);
		for(int i=0;i<this->team.getCount();i++){
			a.team.add(this->team.get(i));
		}
		for(int i=0;i<r.team.getCount();i++){
		   a.team.add(r.team.get(i));
		}
		return a;
	}
	Trainer& operator+=(const Trainer& x){
		for(int i=0;i<x.team.getCount();i++){
			this->team.add(x.team.get(i));
		}
		return *this;
	}
	friend ostream& operator<<(ostream& a,const Trainer& other){
		a<<other.trainerId<<":"<<other.team.getCount()<<endl;
		return a;
	}
	Monster* operator[](int i){
	if(i<0||i>=this->team.getCount()){
		return NULL;
	}
	return&(team.monsters[i]);
	}
	Trainer operator++(){
		int id,hp,level;
		id=rand();
		hp=rand();
		level=rand();
	 this->catchMonster(id,hp,level);	
	 return *this;
	}
};	
int main() {
    srand(100);

    Trainer t1(1);
    t1.catchMonster(25, 80, 5);
    t1.catchMonster(4, 120, 7);

    Trainer t2(2);
    t2.catchMonster(7, 100, 6);
    
    Trainer t3(3);
    t3.catchMonster(1, 110, 6);

    Trainer t4 = t2 + t3;
    t1 += t4;

    t1.releaseMonster(1);
    cout << t1.getAveragePower() << endl;

    t4 = t1;

    for (int i=0; i<3; i++, ++t4);
    cout << t4 << endl;
    
    Monster* m = t4[5];
    if (m != NULL) {
        cout << m->getSpeciesId() << "," << m->getHp() << "," << m->getLevel() << endl;
    }
    else {
        cout << "out of range" << endl;
    }
    return 0;
}