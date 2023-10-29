#pragma once
#include "Components.h"

class ItemComponent : public Component {

public:

	int ID = 1;
	int Weight = 1;
	bool isCarried = false;

	ItemComponent(int id, int weight) {
		ID = id;
		Weight = weight;
	}

	
};