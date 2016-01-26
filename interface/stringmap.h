#ifndef STRINGMAP
#define STRINGMAP
#include <map>
#include <string.h>
#include <iostream>
#include <exception>
using namespace std;

//stringmap is a wrapper class for map<std::string, whatever>
//with guards against segfaults from calling strings not in the map. 
//If the index string is not found you can default or throw an exception. 

//Example use:
//stringmap<int> mymapthing();
//mymapthing.set("green",5);
//int whatisfive = mymapthing.getquick("green",-1);
//try{
//   cout<<"dangerous critter "<<mymapthing.get_throwable("donkey",2)<<endl;
//}
//catch(std::pair <std::string,int> errorpair){
//   cerr<<"Error in stringmap: Invalid string key "<<errorpair.first<< " code "<<errorpair.second<<endl;
//   std::terminate();
//}
//
//Example Map Looping 
//stringmap<bool>* kinvarSwitches = new stringmap<bool>();
//for( std::map<std::string,KinematicVar *>::iterator thisKinvar = allKinVars->begin(); thisKinvar != allKinVars->end(); thisKinvar++) {
//            kinvarSwitches->set(thisKinvar->second->tag,false); 
//}

template <class t> class stringmap{
	public:
		void set(string stringIndex, t item){ tmap[stringIndex] = item; }
		t get(string stringIndex, t default_); //returns default_ if stringIndex not found; no throws guarente. 
		t get_throwable(string stringIndex, int errorcode = 0); //throws pair<string,int> if stringIndex not found

		typename std::map<std::string,t>::iterator begin();
		typename std::map<std::string,t>::iterator end();
		virtual ~stringmap(){
		    //for( std::map<std::string,t>::iterator i = tmap.begin(); i != tmap.end(); i++) delete *i;
		}
	protected:
		std::map<std::string,t> tmap;
}; //end stringmap


template <class t> t stringmap<t>::get(string stringIndex, t default_){
	if(tmap.find(stringIndex) != tmap.end()) return tmap[stringIndex];
	else return default_;
} //end get


template <class t> t stringmap<t>::get_throwable(string stringIndex, int errorcode){
	//Attempts to return the value indexed by stringIndex. 
	//if not found, throws pair<string,int>		= <stringIndex, errorcode>
	if(tmap.find(stringIndex) != tmap.end()) return tmap[stringIndex];
	else{
		std::pair <std::string,int> errorpair (stringIndex,errorcode);
		 throw errorpair;
	}
} //end get_throwable

template <class t> typename std::map<std::string,t>::iterator stringmap<t>::begin(){
	return tmap.begin();
}

template <class t> typename std::map<std::string,t>::iterator stringmap<t>::end(){
	return tmap.end();
}

//typedef stringmap<bool> namedbool;
//typedef stringmap<int> namedint;
//typedef stringmap<float> namedfloat;
typedef stringmap<string> namedstring;

class namedint: public stringmap<int>{
        public:
	void touch(string Label, int init = 0){ //if the label doesn't exist, add it to the list with value init
                if(tmap.find(Label) == tmap.end()) tmap[Label] = init;
        }
        int increment(string Label){ //increment it if it exists
                if(tmap.find(Label) != tmap.end()) return ++tmap[Label];
                else{
		    touch(Label,1);
		    return 1;
		}
        }
        int decrement(string Label){
                if(tmap.find(Label) != tmap.end()) return --tmap[Label];
                else{
		    touch(Label,-1);
		    return -1;
		}
        }
        int add(string Label, int x){ //map[label] += x
                if(tmap.find(Label) != tmap.end()) return tmap[Label]+= x;
                else{
		    touch(Label,x);
		    return x;
		}
        }
        int subtract(string Label, int x){ //map[label] -= x
                if(tmap.find(Label) != tmap.end()) return tmap[Label]-= x;
                else{
		    touch(Label,-x);
		    return -x;
		}
        }
	virtual ~namedint(){}
};// end namedint

class namedbool: public stringmap<bool>{
        public:
	void touch(string Label, bool init =false){ //if the label doesn't exist, add it to the list with value init
                if(tmap.find(Label) == tmap.end()) tmap[Label] = init;
        }
        bool flip(string Label){
                if(tmap.find(Label) != tmap.end()) return tmap[Label] ^= true; //flip the bool and return the new value
                else{
                        cerr<<"Warning! in namedbool.flip received Invalid key string "<<Label<< endl;
                        return false;
                }
        }
        bool or_with(string Label, bool x){
                if(tmap.find(Label) != tmap.end()) return tmap[Label] |= x;
                else{
			touch(Label,x); //if label doesn't exist, make it, init to false, then do operation
                        return x;
                }
        }
        bool xor_with(string Label, bool x){
                if(tmap.find(Label) != tmap.end()) return tmap[Label] ^= x;
                else{
                        cerr<<"Warning! in namedbool.xor_with received Invalid key string "<<Label<< endl;
                        return false;
                }
        }
        bool and_with(string Label, bool x){
                if(tmap.find(Label) != tmap.end()) return tmap[Label] &= x;
                else{
                        touch(Label,x); //if label doesn't exist, make it, init to true, then do operation
                        return x;
                }
        }
	virtual ~namedbool(){}
};//en namedbool

class namedfloat: public stringmap<float>{
        public:
	void touch(string Label, float init = 0.){ //if the label doesn't exist, add it to the list with value init
                if(tmap.find(Label) == tmap.end()) tmap[Label] = init;
        }
        float add(string Label, float x){ //map[label] += x
                if(tmap.find(Label) != tmap.end()) return tmap[Label]+= x;
                else{
                        touch(Label,x); //if label doesn't exist, make it, init to 0, then do operation. 
                        return x;
                }
        }
        float subtract(string Label, float x){ //map[label] -= x
                if(tmap.find(Label) != tmap.end()) return tmap[Label]-= x;
                else{
                        touch(Label,-x); //if label doesn't exist, make it, init to 0, then do operation. 
                        return -x;
                }
        }
        float multiply(string Label, float x){ //map[label] *= x
                if(tmap.find(Label) != tmap.end()) return tmap[Label]*= x;
                else{
                        cerr<<"Warning! in namedfloat.multiply received Invalid key string "<<Label<< endl;
                        return 0.;
                }
        }
        float divide(string Label, float x){ //map[label] /= x
                if(tmap.find(Label) != tmap.end()) return tmap[Label]/= x;
                else{
                        cerr<<"Warning! in namedfloat.multiply received Invalid key string "<<Label<< endl;
                        return 0.;
                }
        }
	virtual ~namedfloat(){}
};//end namedfloat

#endif
