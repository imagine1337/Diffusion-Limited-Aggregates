#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <Window/Mouse.hpp>

using namespace sf;
using namespace std;

class node {
	public:
		int x;
		int y;
};

vector<node> Nodes;
vector<node> stickyNodes;

int r = 3;

int constrain(int n, int l, int h){
	return max(min(n,h),l);
}

void addNode(int x, int y){
	node newNode;
	newNode.x = x;
	newNode.y = y;
	Nodes.push_back(newNode);
}

void addNodes(int n){
	for (int i = 0; i <= n; i++){
		node newNode;
		newNode.x = rand() % 600;
		newNode.y = rand() % 600;
		Nodes.push_back(newNode);
	}
}

int handleNode(node Node) {
	for (int i = 0; i <= stickyNodes.size(); i++){
		int d = sqrt(pow((Node.x-stickyNodes[i].x),2)+pow((Node.y-stickyNodes[i].y),2));
		if (d <= r*2){
			Nodes.erase(Nodes.begin());
			stickyNodes.push_back(Node);
			//addNodes(0);
			return 0;
		}
	}
	Nodes.erase(Nodes.begin());
	Nodes.push_back(Node);
	return 1;
}

int main(){
	node root;
	root.x = 300;
	root.y = 300;
	stickyNodes.push_back(root);
	addNodes(0);
	//addNodes(12); //n of floating particles 
	RenderWindow window(VideoMode(600,600), "Diffusion Limited Aggregate");
	CircleShape shape(r);
	shape.setFillColor(Color(255,255,255));
	int x = 300;
	int y = 300;
	while (window.isOpen()){;
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed){
				window.close();
			} else if (event.type == Event::MouseButtonPressed){
				Vector2i pos = Mouse::getPosition(window);
				addNode(pos.x,pos.y);
			}
		}
		window.clear();
		for (int i = 0; i <= stickyNodes.size(); i++){
			shape.setPosition(stickyNodes[i].x,stickyNodes[i].y);
			window.draw(shape);
		}
		for (int i = 0; i <= Nodes.size(); i++){
			Nodes[0].x=constrain(Nodes[0].x+((rand() % 3) - 1),0,600);
			Nodes[0].y=constrain(Nodes[0].y+((rand() % 3) - 1),0,600);
			shape.setPosition(Nodes[0].x, Nodes[0].y);
			handleNode(Nodes[0]);
			window.draw(shape);
		}
		window.display();
	}
	return 0;
}
