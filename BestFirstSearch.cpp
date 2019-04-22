#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

vector<item> items; // vector of all items
vector<int> bestSet; //the best solution we have right now, bestSet[i].include==1 means item i is in the current solution
int champ; // highest total price so far
int n; //total amount of items to choose from
int C; //capacity of knapsack

int finalProfit=0; // final profit, will be printed into output
int finalSize=0; //final size, will be printed into output
int nodesVisited=0; // total nodes visited, will be printed into output
int leavesVisited=0; // total leaves visited, will be printed into output
node root; // root node, for output
node lastNode; //last node visited, for output




class item{
	public:

	int w; // weight of item
	int p; // price of item
//	bool include; // is item included in current solution?

};

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


struct betterThan{
	bool operator()(node const& n1, node const& n2){
		return n1.upperBound > n2.upperBound;
	}
};

priority_queue<node, vector<node>, betterThan> Q;


int KWF(int profit, int weight, int item){
	int best = profit; //the best profit you can get, by the KWF
	int heavy = weight; //total weight of knapsack
	for(int i = item; i < n; i++){
		if(heavy+ items[i].include <= C){
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
	if(weight > C){
		leavesVisited++;
	}
	if(weight <= C &&  nodei.profit > champ){
		champ = nodei.profit;
		bestSet = nodei.input;
	}
	if(nodei.upperBound < champ){
		leavesVisited++;
	}else{
		int fractionTaken = KWF(nodei.profit, nodei.weight, itemi); //KWF if current item is put into sack
		int fractionNont = KWF(nodei.profit, nodei.weight, itemi+1); //KWF if current item is not put into sack
		nodei.takenptr = newNode( (nodei.itemNum+1) ,  (nodei.profit+items[itemi+1].p) , (nodei.weight+items[itemi+1].w) , fractionTaken);
		nodei.nontakenptr = newNode( (nodei.itemNum+1) , nodei.profit, nodei.weight, fractionNont);
		nodei.takenptr.include = nodei.include;
		nodei.nontakenptr.include = nodei.include;
		nodei.takenptr.include[nodei.itemNum+1] = true;
		nodei.nontakenptr.include[nodei.itemNum+1] = true;


		Q.push(nodei.takenptr);
		Q.push(nodei.nontakenptr);
	}
	if(!Q.empty()){
		node next; //holds teh values of the next node
		next = Q.pop();
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



int main(int argc, char *arv[]){



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

	while(getline(ifile, line){
//		stringstream liner(line);
		getline(liner, argu, ',');
		val = stoi(argu);
		getline(liner, argu, ',');
		val2 = stoi(argu);
		item temp; // temp item to transfer from input file to vector
		temp.w = val;
		temp.p = val2;
		temp.include = false;
		items.push_back(temp);

	}

	ifile.close();


	// SORT GOES HERE


	//KNAPSACK GOES HERE

		








}



