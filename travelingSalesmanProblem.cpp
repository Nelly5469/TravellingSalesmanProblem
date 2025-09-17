// TRAVELLING SALESMAN PROBLEM
#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    string name;                  // Nombre de la ciudad
    vector<Node *> childrenNodes; // Ciudades donde hay viajes directos desde la ciudad actual
    Node *parentNode;

    Node(string cityName) : name(cityName) {} // Constructor para inicializar el nombre de la ciudad
};

class Graph
{
public:
    vector<Node *> nodes; // Almacena los nodos del grafo

    void addNode(const string &cityName)
    {
        nodes.push_back(new Node(cityName)); // Agrega un nuevo nodo al grafo
    }

    void addEdge(const string &fromCity, const string &toCity)
    {
        Node *fromNode = findNode(fromCity);
        Node *toNode = findNode(toCity);
        if (fromNode && toNode)
        {
            fromNode->childrenNodes.push_back(toNode); // Establece la conexi�n entre las ciudades
            // toNode->parentNodes.push_back(fromNode);
        }
    }

    Node *findNode(const string &cityName)
    {
        for (Node *node : nodes)
        {
            if (node->name == cityName)
            {
                return node; // Devuelve el nodo si se encuentra
            }
        }
        return nullptr; // Devuelve nullptr si no se encuentra
    }

    void displayGraph()
    {
        for (Node *node : nodes)
        {
            cout << "Ciudad: " << node->name << " -> ";
            for (Node *child : node->childrenNodes)
            {
                cout << child->name << " ";
            }
            cout << endl;
        }
    }

    ~Graph()
    {
        for (Node *node : nodes)
        {
            delete node; // Libera la memoria de los nodos
        }
    }
};

int main()
{
    Graph graph;

    // Inicializa las ciudades
    const vector<string> CITIES = {"NY", "CHI", "DEN", "HOU", "URB", "LA", "TOR", "CALG"};

    vector<vector<Node *>> solutions;

    // Agrega nodos al grafo
    for (const string &city : CITIES)
    {
        graph.addNode(city);
    }

    // Establece conexiones entre las ciudades (aristas)
    //graph.addEdge("NY", "CHI"); // **
    graph.addEdge("NY", "TOR");
    graph.addEdge("NY", "DEN");   // ** Si le paso primero el camino mas corto, lo hace mal
    graph.addEdge("NY", "CHI");
    graph.addEdge("CHI", "DEN");
    //graph.addEdge("TOR", "LA"); // *
    graph.addEdge("DEN", "HOU");
    graph.addEdge("DEN", "LA");
    graph.addEdge("HOU", "URB");
    graph.addEdge("HOU", "LA");
    graph.addEdge("TOR", "CALG"); // * Si le paso primero el camino mas largo, lo hace bien
    graph.addEdge("TOR", "LA");
    graph.addEdge("CALG", "LA");

    // Muestra el grafo
    graph.displayGraph();

    Node *INIT_STATE = graph.findNode("NY");
    Node *FINAL_STATE = graph.findNode("LA");
    if (INIT_STATE == nullptr || FINAL_STATE == nullptr)
    {
        cout << "Error: uno de los nodos no se encontró." << endl;
        return -1; // O maneja el error de otra manera
    }
    // 1. Lista abierta contiene el edo. inicial
    stack<Node *> openList;
    openList.push(INIT_STATE);
    // 2. Lista cerrada vacia
    stack<Node *> closedList;

    Node *currentNode;
    Node *auxNode, *auxNode2;
    unsigned int i;
    vector<Node *> currentSolution;

    // 3. Lista abierta vacia?
    while (!openList.empty())
    {
        // 3.1 No
        currentNode = openList.top(); // 3.1.1 Nodo actual en lista abierta
        // 3.1.2 Nodo actual en lista cerrada (extraer de lista cerrada)
        closedList.push(currentNode);
        openList.pop();
        if (closedList.top() != FINAL_STATE)
        { // 3.1.3
            // 3.1.3.1
            for (Node *children : currentNode->childrenNodes)
            {                            // 3.1.3.1.1
                openList.push(children); // 3.1.3.1.2
                ////3.1.3.1.3 Establecer apuntadores desde descendientes incorporado hacia padre en lista cerrada
                children->parentNode = currentNode;
            }
        }
        else
        {
            auxNode = closedList.top();
            //while (auxNode != INIT_STATE)
            while (auxNode != INIT_STATE && auxNode != nullptr)
            {
                currentSolution.push_back(auxNode);
                auxNode2 = auxNode->parentNode;
                //auxNode->parentNode = nullptr; // quitar ref a padre //deberia agregar una bandera a los padres ya visitados?
                auxNode = auxNode2;
            }
            solutions.push_back(currentSolution);
            //sol: cada que  se encuentre una solucion quitar todos los nodos padres
            currentSolution.clear();
        }
    }

    // mostrar soluciones
    cout << endl
         << endl
         << "Trayectorias de soluciones" << endl;
    for (vector <Node *> solution : solutions)
    {
        for (Node *city : solution)
        {
            cout << city->name << " ";
        }
        cout << endl;
    }

    return 0;
}
