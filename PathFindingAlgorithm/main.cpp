#include<string>
#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
#include<deque>
#include<stack>
#include<queue>
using namespace std;
//enum diraction {forward, backward,both};

class paths{
    public:
    string from;
    string to;
    int cost;
    paths(string start, string finish,int cost){
        this->from=start;
        this->to=finish;
        this->cost=cost;
    }
};
// class vertices{
//     public:
//     string name;
//     vertices* previous;
//     int mincost;
//     vertices(string name, int min=INT_MAX, vertices* pre=NULL){
//         this->name=name;
//         this->previous=pre;
//         this->mincost=min;
//     }
// };
class map{
    public:
    vector<paths> allpaths;
    map (string filename){
        ifstream file;
        file.open(filename);
        string line;
        while (getline(file,line)){
            stringstream ss(line);
            string name[3];
            for (int i=0;i<3;i++){
                getline(ss,name[i],' ');
            }
            paths newpath=paths(name[0],name[1], stoi(name[2]));
            allpaths.push_back(newpath);
        }
        file.close();
    }
    void showpaths(){
        for (int i=0;i<allpaths.size();i++){
            cout<<allpaths[i].from<<"-"<<allpaths[i].cost<<"->"<<allpaths[i].to<<endl;
        }
    }
    bool find_cost_path(string destination, deque<vector<string>> &tracklist, deque<int>&cost){
        vector<string> track=tracklist.front();
        if (track.back()==destination) return true;
        for (int i=0;i<allpaths.size();i++){
            if (track.back()==allpaths[i].from){
                bool loop=false;
                for (auto j=track.begin();j<track.end();j++){ 
                    if(allpaths[i].to==*j) {
                        loop=true;
                        break;
                    }
                }
                if (loop) continue;
                vector<string> newtrack=track;
                newtrack.push_back(allpaths[i].to);
                tracklist.push_back(newtrack);
                int newcost =cost.front()+allpaths[i].cost;
                cost.push_back(newcost);
            }
        }
        tracklist.pop_front();
        cost.pop_front();
        return false;
    }
    void BFS_least_expensive_path(string innitial, string destination){
        deque<vector<string>> tracks;
        deque<vector<string>> right_tracks;
        deque<int> costs;
        deque<int> right_costs;
        costs.push_back(0);
        vector<string> vect1 {innitial};
        tracks.push_back(vect1);
        while (!tracks.empty()){
            if (find_cost_path(destination,tracks,costs)){
                right_tracks.push_back(tracks.front());
                tracks.pop_front();
                right_costs.push_back(costs.front());
                costs.pop_front();
            }
        }
        if (right_tracks.empty()){
            cout<<"destination is either not exist or unreachable!";
            return;
        }
        int min=0;
        for (int i=1;i<right_costs.size();i++) if (right_costs[i]<right_costs[min]) min=i;
        cout<<"the least expensive rount is: "<<right_tracks[min][0];
        for (int i=1;i<right_tracks[min].size();i++) cout<<"->"<<right_tracks[min][i];
        cout <<" which cost: "<<right_costs[min]<<"\nother possible rount are:"<<endl;
        for (int j=0;j<right_tracks.size();j++){
            if (j==min)continue;
            cout<<right_tracks[j][0];
            for (int i=1;i<right_tracks[j].size();i++) cout<<"->"<<right_tracks[j][i];
            cout <<"\twhich cost: "<<right_costs[j]<<endl;
        }
    }
};
// class BILL_FORD_search: public map{
//     public:
//     BILL_FORD_search(string innitial, string destination) : map(filename) {
//         vertice.push_back(new vertices(innitial,0));
//         while (true){
//             bool end=true;
//             for (int i=0;i<vertice.size();i++){
//                 for (int j=0;j<allpaths.size();j++){
//                     if (vertice[i]->name==allpaths[j].from){
//                         vertices *newvertice=NULL;
//                         vertices *prevertice=NULL;
//                         for (int h=0;h<vertice.size();h++){
//                             if(allpaths[j].to==vertice[h]->name) vertice[h]=newvertice;
//                             if(allpaths[j].from==vertice[h]->name) vertice[h]=prevertice;
//                         }
//                         if (!newvertice) {
//                             newvertice=new vertices(allpaths[j].to);
//                             vertice.push_back(newvertice);
//                         }
//                         if (newvertice->mincost>prevertice->mincost+allpaths[j].cost) {
//                             newvertice->mincost=prevertice->mincost+allpaths[j].cost;
//                             newvertice->previous=prevertice;
//                             end=false;
//                         }
//                     }
//                 }
//             }
//             if (end) break;
//         }
//         vertices*dest;
//         for (int i=0;i<vertice.size();i++){
//             if (destination==vertice[i]->name)dest=vertice[i];
//         }
//         if (!dest){
//             cout<<"destination is either not exit or unreachable.";
//             return;
//         }
//         cout<<"the least expensive path is:"<<endl;
//         int cost=0;
//         print_path(dest,cost);
//         cout<<" (which cost "<<cost<<"$)"<<endl;
//     }
//     vector<vertices*> vertice;
//     bool update=false;
//     void print_path(vertices *now, int &cost){
//         cost+=now->mincost;
//         if (!now->previous){
//             cout<<now->name;
//             return;
//         }
//         print_path(now->previous,cost);
//         cout<<" -> "<<now->name;
//         return;
//     }
// };
int main(){
    string str = "shape.txt";
    map shape(str);
    shape.showpaths();
    // BILL_FORD_search bfs(str,"a","k");
    shape.BFS_least_expensive_path("a","k");
    return 0;
}