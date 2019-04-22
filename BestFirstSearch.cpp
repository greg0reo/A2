#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

vector<item> items; // vector of all items
vector<item> bestSet; //the best solution we have right now, bestSet[i].include==1 means item i is in the current solution
int n; //total amount of items to choose from
int C; //capacity of knapsack

class item{
	public:

	int w; // weight of item
	int p; // price of item
	bool include; // is item included in current solution?

};

class node{
	public:

	int profit; //The total money currently in the sack
	int weight; // the total weight currently in the sack
	int upperBound; // the total max profit possible to gain at this moment

};


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


node newNode(int item, int profit, int weight, int maxprofit){
	node temp; //creates new node to insert into tree
	temp.profit = profit;
	temp.weight = weight;
	temp.upperBound = maxprofit;
	return temp;

}




int main(int argc, char *arv[]){

	int finalProfit=0;
	int finalSize=0;
	int nodesVisited=0;
	int leavesVisited=0;
	node root;
	node lastNode;

	//READ IN ITEMS FROM FILE HERE


	// SORT GOES HERE


	//KNAPSACK GOES HERE

		








}



