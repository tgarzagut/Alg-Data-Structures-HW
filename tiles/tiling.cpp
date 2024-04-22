
#include "tiling.h"
#include "vertex.h"

using namespace std;


// Finds a (shortest according to edge length) augmenting path
// from s to t in a graph with vertex set V.
// Returns whether there is an augmenting path.
bool augmenting_path(Vertex* s, Vertex* t, 
        unordered_set<Vertex*> V, vector<Vertex*> &P)
{
        // Check that s and t aren't nullptr
        if (s == nullptr || t == nullptr)
	{
		cerr << "augmenting_path() was passed nullptr s or t." << endl;
		abort();
	}

        // Check that s and t are in the graph
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "augmenting_path() was passed s or t not in V." << endl;
		abort();
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "augmenting_path() was passed invalid vertex." << endl;
				abort();
			}

        // Since augmenting paths should have the fewest edges,
	// not the minimum weight, run BFS.
	queue<Vertex*> Q;
	Q.push(s);

	unordered_set<Vertex*> R;
	R.clear(); 
	R.insert(s);

	unordered_map<Vertex*, Vertex*> prev;

	while (!Q.empty())
	{
		Vertex* cur = Q.front();
		Q.pop();

		for (Vertex* nei : cur->neighs)
		{
			// Must have positive edge weight
			if (cur->weights[nei] == 0)
				continue;

			if (R.find(nei) == R.end())
			{
				Q.push(nei);
				R.insert(nei);
				prev[nei] = cur; 
			}
		}
	}      

        // If BFS never reached t
        if (R.find(t) == R.end())
                return false;

        // Reconstruct shortest path backwards
        P.clear();
        P.push_back(t);
        while (P[P.size()-1] != s)
                P.push_back(prev[P[P.size()-1]]);

        // Reverse shortest path
        for (int i = 0; i < P.size()/2; ++i)
		swap(P[i], P[P.size()-1-i]);

        return true;
}

// Returns the maximum flow from s to t in a weighted graph with vertex set V.
// Assumes all edge weights are non-negative.
int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
{
	// If s or t is invalid.
        if (s == nullptr || t == nullptr)
	{
		cerr << "max_flow() was passed nullptr s or t." << endl;
		abort(); 
	}

	// If s or t is not in the vertex set.
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "max_flow() was passed s or t not in V." << endl;
		abort(); 
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "max_flow() was passed invalid vertex." << endl;
				abort();
			}

        // Create a deep copy of V to use as the residual graph
        unordered_set<Vertex*> resV;
        unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
        for (Vertex* vp : V)
        {
                Vertex* rp = new Vertex;
                resV.insert(rp);
                C[vp] = rp;
        }
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
                {
                        C[vp]->neighs.insert(C[np]);
                        C[vp]->weights[C[np]] = vp->weights[np];
                }
	// Add any missing necessary "back" edges. 
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
		{
			if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
			{
				C[np]->neighs.insert(C[vp]);
				C[np]->weights[C[vp]] = 0;
			}
		}

        // Run Edmonds-Karp
        while (true)
        {
                // Find an augmenting path
                vector<Vertex*> P;
                if (!augmenting_path(C[s], C[t], resV, P))
                        break;  
                // Update residual graph
                for (int i = 0; i < P.size()-1; ++i)
                {
                        --((*(resV.find(P[i])))->weights[P[i+1]]);
                        ++((*(resV.find(P[i+1])))->weights[P[i]]);
                }
        }

        // Compute actual flow amount
        int flow = 0;
        for (Vertex* snp : C[s]->neighs)
                flow += 1 - C[s]->weights[snp];

        // Delete residual graph
        for (Vertex* vp : resV)
                delete vp;

        return flow;
}


bool has_tiling(string floor){

	unordered_set <Vertex*> colorTable;
    vector<vector<Vertex*> > graph;
	vector<vector<string> > tileColors;
	Vertex* start = new Vertex;
	Vertex* end = new Vertex;
	colorTable.insert(start);
	colorTable.insert(end);
	int numVertex = 0;
	int numRows = 0;
	int numCols = 0;

	for(int i = 0; i < floor.length(); ++i) {
    	if(floor[i] != '\n') {
			Vertex* newVertex = new Vertex;
			string dotColor;

			if(numCols == 0) {
				graph.push_back(vector<Vertex*>());
				tileColors.push_back(vector<string>());
			}
			graph[numRows].push_back(newVertex);

			if((numRows + numCols) % 2 == 0) {
				dotColor = "red";
			} else {
				dotColor = "blue";
			}
			//if its a # then no color
			if(floor[i] == '#') {
				dotColor = "none";
			}

			tileColors[numRows].push_back(dotColor);
			numCols += 1;
		}
		else {
			numRows += 1;
			numCols = 0;
		}
	} 

	for(int i = 0; i < graph.size(); i++){
		for(int j = 0; j < graph[i].size(); j++){
			if(tileColors[i][j] == "red"){
				if(tileColors[i][j - 1] != "none" && j - 1 > -1){
					graph[i][j]->neighs.insert(graph[i][j - 1]);
					graph[i][j]->weights[graph[i][j - 1]] = 1;
				}
				if(tileColors[i - 1][j] != "none" && i - 1 > -1){
					graph[i][j]->neighs.insert(graph[i - 1][j]);
					graph[i][j]->weights[graph[i - 1][j]] = 1;
				}
				if(tileColors[i][j + 1] != "none" && j + 1 < tileColors[i].size()){
					graph[i][j]->neighs.insert(graph[i][j + 1]);
					graph[i][j]->weights[graph[i][j + 1]] = 1;
				}
				if(tileColors[i + 1][j] != "none" && i + 1 < tileColors.size()){
					graph[i][j]->neighs.insert(graph[i + 1][j]);
					graph[i][j]->weights[graph[i + 1][j]] = 1;
				}
			}
			int x = i + j;
			if(tileColors[i][j] != "none" && x % 2 == 1){
				graph[i][j]->neighs.insert(end);
				graph[i][j]->weights[end] = 1;
				colorTable.insert(graph[i][j]);
				numVertex += 1;
			}
			else if(tileColors[i][j] != "none" && x % 2 == 0){
				start->neighs.insert(graph[i][j]);
				start->weights[graph[i][j]] = 1;
				colorTable.insert(graph[i][j]);
				numVertex += 1;
			}
		}	
	}

	if(numVertex/2 == max_flow(start, end, colorTable) && colorTable.size() % 2 == 0){
		return true;
	}
	else{
		return false;
	}
}




