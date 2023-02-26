#include <bits/stdc++.h>

using namespace std;

/********************Note from Prashant Shishodia***********************/
// This program finds a stable matching between n girls and boys
// The algorithm description can be found on http://cse.iitkgp.ac.in/~palash/Courses/2019AlgorithmicGameTheory/Files/2019AlgorithmicGameTheoryLectureNotes.pdf
// Refer Section : 11.1 Stable Matching
// This program was developed one night before our Game Theory Exam
// Because we were motivated by the fact that we could understand this section but everything else
// And the motivation that all we need is n girls to get laid no matter how ugly we're
// Didn't you read the theorem? 
// Credits : Sanket Mesharam for his valuable emotional and destructive support
// arising from his desparation and neediness. 

/****************Note from Sanket Mesharam******************/
//This algorithm enabled Prashant Shishodia to get relief from his singlehood 
// (not denying the fact how ugly he is), and finally get laid. His hand must be having a
// sigh of relief right now. What are you waiting for ? 

int main(){
    cout<<"Enter the number of couples needed\n"; 
    int n; cin>>n; 
    vector<string> boy_name(n), girl_name(n); 
    map<string, int> boys; 
    map<string, int> girls; 
    cout<<"Enter the name of all boys\n"; 

    for(int i = 0;i < n; ++i){
        string boy; cin>>boy_name[i]; boys[boy_name[i]] = i; 
    }

    cout<<"Cool ! Enter the name of all girls now\n";  
    for(int i = 0;i < n; ++i){
        string girl; cin>>girl_name[i]; girls[girl_name[i]] = i; 
    }

    vector<vector<int> > priority_boy(n, vector<int> (n)); 
    vector<vector<int> > pos_girl(n, vector<int> (n)); 

    cout<<"Boys priority order time \n"; 
    for(auto p : boys){
        string boy = p.first; int id = p.second; 
        cout<<boy<<" : Enter girls name in priority order\n"; 
        for(int i = 0;i < n; ++i){
            string girl; cin>>girl; 
            priority_boy[id][n - i - 1] = girls[girl]; 
        }
    }

    cout<<"Girls priority order time \n"; 
    for(auto p : girls){
        string girl = p.first; int id = p.second; 
        cout<<girl<<" : Enter boys name in priority order\n"; 

        for(int i = 0;i < n; ++i){
            string boy; cin>>boy; 
            pos_girl[id][boys[boy]] = i; 
        }
    }


    // my fucking algorithms starts here. 
    // You all are getting laid. LMAO 

    vector<int> girl_partner_id(n, -1); 

    set<int> unmatched_men; 
    for(int i = 0;i < n; ++i)unmatched_men.insert(i); 

    while(!unmatched_men.empty()){
        int curr_boy = *unmatched_men.begin(); 
        int curr_girl = priority_boy[curr_boy].back(); 
        priority_boy[curr_boy].pop_back(); 

        int curr_partner = girl_partner_id[curr_girl]; 
        if(curr_partner == -1){   // girl isn't laid yet. 
            girl_partner_id[curr_girl] = curr_boy; 
            unmatched_men.erase(curr_boy); 

        }else if(pos_girl[curr_girl][curr_partner] > pos_girl[curr_girl][curr_boy]){
            girl_partner_id[curr_girl] = curr_boy; 
            unmatched_men.erase(curr_boy); unmatched_men.insert(curr_partner); 
        }
    }

    cout<<"The algorithm has terminated !!";  
    cout<<"Best possible partners are :  \n"; 
    for(int i = 0;i < n; ++i){
        string girl = girl_name[i]; 
        string boy = boy_name[girl_partner_id[i]]; 
        cout<<girl<<" gets laid with "<<boy<<"\n"; 
    }
    return 0; 
}
