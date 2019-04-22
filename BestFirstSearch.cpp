#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>
#include <string>
#include <chrono>

using namespace std;

vector<int> bestSet; //the best solution we have right now, bestSet[i].include==1 means item i is in the current solution
int champ; // highest total price so far
int n; //total amount of items to choose from
int C; //capacity of knapsack

int finalProfit=0; // final profit, will be printed into output
int finalSize=0; //final size, will be printed into output
int nodesVisited=0; // total nodes visited, will be printed into output
int leavesVisited=0; // total leaves visited, will be printed into output
//node root; // root node, for output




class item{
	public:

	int w; // weight of item
	int p; // price of item
	double r;
//	bool include; // is item included in current solution?

};

vector<item> items; // vector of all items


class node{
	public:

	int profit; //The total money currently in the sack
	int weight; // the total weight currently in the sack
	int upperBound; // the total max profit possible to gain at this moment
	int itemNum;
	vector<int> include; //the items included in this node
	node * takenptr; // pointer in case next item is taken
	node * nontakenptr; //pointer in case next item is not taken
};

node root; // root node, for output
node lastNode; //last node visited, for output



struct betterThan{
	public:
	bool operator()(node const& n1, node const& n2){
		return n1.upperBound > n2.upperBound;
	}
};

priority_queue<node, vector<node>, betterThan> Q;

struct arComp{
	bool operator() (item i, item j){
		return i.r< j.r;
	}
} useThis;

// timer
int KWF(int profit, int weight, int item){
	int best = profit; //the best profit you can get, by the KWF
	int heavy = weight; //total weight of knapsack
	for(int i = item; i < n; i++){
		if(heavy+ items[i].w <= C){
			best += items[i].p;
			heavy += items[i].w;
		}else{
			int remaining = C- heavy; //remaining weight in sack
			best += (items[i].p)*remaining/(items[i].w);
			heavy = C;
			return best;
		}
	}
}


node newNode(int itemNum, int profit, int weight, int maxprofit){
	node temp; //creates new node to insert into tree
	temp.profit = profit;
	temp.weight = weight;
	temp.upperBound = maxprofit;
	temp.itemNum = itemNum;
//	if(weight >= C){
//		leavesVisited++;
//	}
//	nodesVisited++;
	return temp;

}


void knapsack(node nodei){
	nodesVisited++;
	if(nodei.weight > C){
		leavesVisited++;
	}
	if(nodei.weight <= C &&  nodei.profit > champ){
		champ = nodei.profit;
		bestSet = nodei.include;
	}
	if(nodei.upperBound < champ){
		leavesVisited++;
		lastNode = nodei;
	}else{
		int fractionTaken = KWF(nodei.profit, nodei.weight, nodei.itemNum); //KWF if current item is put into sack
		int fractionNont = KWF(nodei.profit, nodei.weight, nodei.itemNum+1); //KWF if current item is not put into sack
		node ta = newNode( (nodei.itemNum+1) ,  (nodei.profit+items[nodei.itemNum+1].p) , (nodei.weight+items[nodei.itemNum+1].w) , fractionTaken); //temp node for taken path
		node na = newNode( (nodei.itemNum+1) , nodei.profit, nodei.weight, fractionNont); // temp node, for nontaken path
		ta.include = nodei.include;
		na.include = nodei.include;
		ta.include[nodei.itemNum+1] = true;
		na.include[nodei.itemNum+1] = true;

		nodei.takenptr = &ta;
		nodei.nontakenptr = &na;


		Q.push(*nodei.takenptr);
		Q.push(*nodei.nontakenptr);
	}
	if(!Q.empty()){
		node next; //holds teh values of the next node
		next = Q.top();
		Q.pop();
		knapsack(next);
	}
/*
	if(fractionNont > fractionTaken){
		knapsack(itemi+1, nontakenptr);
		items[itemi+1].include = true;
		knapsack(itemi+1, takenptr);
		items[itemi+1].include = false;
	}else{
		items[itemi+1].include = true;
		knapsack(itemi+1, takenptr);
		items[itemi+1].include = false;
		knapsack(itemi+1, nontakenptr);
	}
*/
}



int main(int argc, char *argv[]){


	using namespace std;

	//READ IN ITEMS FROM FILE HERE

	string input = argv[1];
	string output = argv[2];

	ifstream ifile(input);

	string line; // the string where a line from input will be stored
	string argu; // string where a value from the input will be stored
	int val; // int for first value from input
	int val2; //int for second value from input

	getline(ifile, line);
	stringstream liner(line);
	getline(liner, argu, ',');
	val = stoi(argu);
	getline(liner, argu, ',');
	val2 = stoi(argu);
	n = val;
	C = val2;

	while(getline(ifile, line)){
		stringstream liner(line);
		getline(liner, argu, ',');
		val = stoi(argu);
		getline(liner, argu, ',');
		val2 = stoi(argu);
		item temp; // temp item to transfer from input file to vector
		temp.w = val;
		temp.p = val2;
//		temp.include = false;
		items.push_back(temp);

	}

	ifile.close();

	for(int i = 0; i<n; i++){
		items[i].r = items[i].p/items[i].w;
	}

	// SORT GOES HERE

	sort(items.begin(), items.end(), useThis);

	//KNAPSACK GOES HERE
	int fractions; // holds KWF for entire knapsack
	fractions = KWF(0, 0, 0);
	node temp2 = newNode( -1, 0, 0, fractions); //root node for knapsack
	temp2.include = bestSet;
	root = temp2;
	knapsack(temp2);

	cout << champ << endl;





}



