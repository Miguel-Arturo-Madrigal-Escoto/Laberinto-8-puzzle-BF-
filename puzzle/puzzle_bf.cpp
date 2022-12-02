#include <bits/stdc++.h>
#define fore(i,a,b) for(int i = (a), T = b; i < T; ++i)
#define sz(s) int(s.size())
#define all(v) begin(v),end(v)
#define f first
#define s second
#define ENDL '\n'

using namespace std;

typedef vector<vector<int>> state;
typedef pair<state,string>  action;
typedef map<action,action> map_action;
typedef map<state,bool> map_visited;


state move(state temp, string mov){
	/// Movimiento hacia arriba
	if (mov == "up"){
		//Recorrer la matriz del estado temporal
		// i = rows, c = cols
		fore(i,0,3){
			fore(j,0,3){
				// Buscar la posición vacia (-1)
				if(temp[i][j] == -1){
					// Validar que se pueda mover hacia arriba
					if (i != 0){
						// Mover el que esta arriba de -1 a la posición del -1
						temp[i][j] = temp[i-1][j];
						
						// Mover el -1 hacia abajo 
						temp[i-1][j] = -1;
					}
				}
			}
		}
	}
	
	if (mov == "down"){
		//Recorrer la matriz del estado temporal
		// i = rows, c = cols
		fore(i,0,3){
			fore(j,0,3){
				// Buscar la posición vacia (-1)
				if(temp[i][j] == -1){
					// Validar que se pueda mover hacia abajo
					if (i != 2){
						// Mover el que esta abajo de -1 a la posición del -1
						temp[i][j] = temp[i+1][j];
						
						// Mover el -1 hacia abajo
						temp[i+1][j] = -1;
					}
			    }
			}
		}
	}
	
	if (mov == "left"){
		//Recorrer la matriz del estado temporal
		// i = rows, c = cols
		fore(i,0,3){
			fore(j,0,3){
				// Buscar la posición vacia (-1)
				if(temp[i][j] == -1){
					// Validar que se pueda mover hacia la izquierda
					if (j != 0){
						// Mover el que esta izquierda de -1 a la posición del -1
						temp[i][j] = temp[i][j-1];
						
						// Mover el -1 hacia la izquierda
						temp[i][j-1] = -1;
					}
			    }
			}
		}
	}
	
	if (mov == "right"){
		//Recorrer la matriz del estado temporal
		// i = rows, c = cols
		fore(i,0,3){
			fore(j,0,3){
				// Buscar la posición vacia (-1)
				if(temp[i][j] == -1){
					// Validar que se pueda mover hacia la derecha
					if (j != 2){
						// Mover el que esta derecha de -1 a la posición del -1
						temp[i][j] = temp[i][j+1];
						
						// Mover el -1 hacia la derecha
						temp[i][j+1] = -1;
					}
			    }
			}
		}
	}
	return temp;
}


string get_state(state s){
	string out = "";
	fore(i,0,3){
		fore(j,0,3){
			if (s[i][j] != -1) out += to_string(s[i][j]) + " ";
			else out += "  ";
		}
		out += ENDL;
	}
	return out;
}

void reconstruct_path(map_action path, action s, action begin){
	action curr = s;
	stack<action> stack_path;
	while (true){
		stack_path.push(curr);
		if (curr == begin) break;
		
		stack_path.push(path[curr]);
		if (path[curr] == begin) break;
		
		curr = path[path[curr]];
	}
	
	cout << "Movimientos: " << sz(stack_path)-1 << ENDL << ENDL;
	
	while(!stack_path.empty()){
		curr = stack_path.top(); stack_path.pop();
		cout << "Mov: " << curr.s << ENDL;
		cout << get_state(curr.f) << ENDL;
	}
}

void bf(state start, state target){
	int path_cost = 0;
	string out = "";
	map_visited explored;
	map_action path;
	
	action puzzle;
    //Listas (abierta (ordenada) y cerrada)
    vector<action> open;
    vector<action> closed;

    //Meter el nodo inicial a la lista abierta
    open.push_back(make_pair(start,"initial"));
	
	path[{start,"initial"}] = {start,"initial"};
	
	cout << "Expandiendo con BF" << ENDL;
	
	while (open.size() > 0){
        //Mantener ordenada la lista abierta (PQ)
        sort(all(open));

        //Si la lista abierta está vacia
        if (open.empty()){
            break;
        }

        //Mover el nodo en el tope a la lista cerrada
        puzzle = open.back(); open.pop_back();
        closed.push_back(puzzle);
		++path_cost;
		
		out += "Mov: " + puzzle.s + ENDL;
		out += get_state(puzzle.f) + ENDL;
		
		// Si ya llegó al estado meta
		if (puzzle.f == target){
			cout << "Solucion Encontrada" << ENDL;
			cout << "Nodos expandidos: " << to_string(path_cost) << ENDL << ENDL;
			cout << out;  
			break;
		}
		
		// Si aun no ha llegado
		else {
			if (!explored[puzzle.f]){
				explored[puzzle.f] = true;
				
				state temp;
				// Mover hacia arriba
				if (puzzle.s != "down"){
					temp = puzzle.f; 	
					state up = move(temp,"up");
					if (up != puzzle.f){
						action after_up = make_pair(up,"up");
						path[after_up] = puzzle;
						open.push_back(after_up);
					}
				}
				
				// Mover hacia la izquierda
				if (puzzle.s != "right"){
					temp = puzzle.f; 	
					state left = move(temp,"left");
					if (left != puzzle.f){
						action after_left = make_pair(left,"left");
						path[after_left] = puzzle;
						open.push_back(after_left);
					}
				}
				
				// Mover hacia abajo
				if (puzzle.s != "up"){
					temp = puzzle.f; 	
					state down = move(temp,"down");
					if (down != puzzle.f){
						action after_down = make_pair(down,"down");
						path[after_down] = puzzle;
						open.push_back(after_down);
					}
				}
				
				// Mover hacia la derecha
				if (puzzle.s != "left"){
					temp = puzzle.f; 	
					state right = move(temp,"right");
					if (right != puzzle.f){
						action after_right = make_pair(right,"right");
						path[after_right] = puzzle;
						open.push_back(after_right);
					}
				}
			}
		}
	}
	
	reconstruct_path(path,puzzle,{start,"initial"});
}


int main()
{
	// ? Caso 1:
	state start = {
					{1,4,3},
	                {7,-1,6},
	 				{5,8,2}
				  };
	state target = {
					{1,4,3},
					{7,6,2},
					{5,8,-1}
				   };



	// //? Caso 2:
	// state start = {
	// 				{1,2,3},
	// 				{8,-1,4},
	// 				{7,6,5}
	// 			  };
	// state target = {
	// 				{1,2,3},
	// 				{8,4,5},
	// 				{7,-1,6}
	// 			   };

	cout << "BF (Best First Search)" << ENDL;
	bf(start, target);

	return 0;
}