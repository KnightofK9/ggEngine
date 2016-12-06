#include "QuadNode.h"
#include "Body.h"
#include "Rect.h"
#include "Group.h"
#include "GameObject.h"
#include "Game.h"
#include "QuadTree.h"
#include "Add.h"
namespace ggEngine {
	QuadNode::QuadNode(Game *game, QuadTree *quadTree, double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels, unsigned int level)
	{
		this->game = game;
		this->quadTree = quadTree;
		Reset(x, y, width, height, maxObjects, maxLevels, level);
	}
	QuadNode::QuadNode(Game *game, QuadTree *quadTree, const char * quadNodeJson)
	{
		this->game = game;
		this->quadTree = quadTree;
		Json json(quadNodeJson);
		double x, y, width, height;
		unsigned int maxObjects, maxLevels, level;

		maxLevels = json["maxLevels"].GetInt();
		maxObjects = json["maxObjects"].GetInt();
		auto& bounds = json["bounds"];
		x = bounds["x"].GetDouble();
		y = bounds["y"].GetDouble();
		width = bounds["width"].GetDouble();
		height = bounds["height"].GetDouble();
		
		Reset(x, y, width, height, maxObjects, maxLevels, level);

		for (auto& obj : json["objects"].GetArray()) {
			std::string type = obj["type"].GetString();
			double x = obj["x"].GetDouble();
			double y = obj["y"].GetDouble();
			GameObject* go = game->add->AddObjectBaseOnType(type);
			go->SetParentObject(this->quadTree);
			go->SetPosition(x, y);
			this->quadTree->AddDrawObjectToList(go);
			this->objects.push_back(go->body);
		}
		auto nodeArray = json["nodes"].GetArray();
		if (nodeArray.Size() > 0) {
			this->nodes.reserve(4);
		}
		for (auto& node : nodeArray) {
			const char* nodeJson = node.GetString();
			this->nodes.push_back(new QuadNode(this->game, this->quadTree, nodeJson));
		}
	}
	QuadNode::~QuadNode()
	{
		Clear();
	}

	void QuadNode::Reset(double x, double y, double width, double height, unsigned int maxObjects, unsigned int maxLevels, unsigned int level)
	{
		this->maxObjects = maxObjects;
		this->maxLevels = maxLevels;
		this->level = level;

		this->bounds.x = round(x);
		this->bounds.y = round(y);
		this->bounds.width = width;
		this->bounds.height = height;
		this->bounds.subWidth = floor(width / 2);
		this->bounds.subHeight = floor(height / 2);
		this->bounds.right = this->bounds.x + this->bounds.subWidth;
		this->bounds.bottom = this->bounds.y + this->bounds.subHeight;

		this->objects.clear();
		this->nodes.clear();

	}

	void QuadNode::Populate(Group * group)
	{
		InsertFromDrawList(group->GetDrawList());
		auto groupList = group->GetGroupList();
		for (auto it = groupList->begin(); it != groupList->end(); ++it) {
			InsertFromDrawList((*it)->GetDrawList());
		}
	}

	void QuadNode::Split()
	{
		this->nodes.resize(4);
		nodes[0] = new QuadNode(this->game,this->quadTree,this->bounds.right, this->bounds.y, this->bounds.subWidth, this->bounds.subHeight, this->maxObjects, this->maxLevels, (this->level + 1));
		
		//  top left node
		nodes[1] = new QuadNode(this->game, this->quadTree, this->bounds.x, this->bounds.y, this->bounds.subWidth, this->bounds.subHeight, this->maxObjects, this->maxLevels, (this->level + 1));

		//  bottom left node
		nodes[2] = new QuadNode(this->game, this->quadTree, this->bounds.x, this->bounds.bottom, this->bounds.subWidth, this->bounds.subHeight, this->maxObjects, this->maxLevels, (this->level + 1));

		//  bottom right node
		nodes[3] = new QuadNode(this->game, this->quadTree, this->bounds.right, this->bounds.bottom, this->bounds.subWidth, this->bounds.subHeight, this->maxObjects, this->maxLevels, (this->level + 1));

	}

	void QuadNode::Insert(Body * body)
	{
		int i = 0;
		int index;
		if (this->nodes.size() > 0) {
			index = GetIndex(body->GetRect());

			if (index != -1) {
				this->nodes[index]->Insert(body);
				return;
			}
		}

		this->objects.push_back(body);

		if (this->objects.size() > this->maxObjects && this->level < this->maxLevels) {
			if (this->nodes.size() > 0) {
				Split();
			}

			while (i < this->objects.size()) {
				index = GetIndex(this->objects[i]->GetRect());

				if (index != -1) {
					this->nodes[index]->Insert(this->objects[i]);
					this->objects.erase(std::remove(this->objects.begin(), this->objects.end(), this->objects[i]), this->objects.end());
				}
				else {
					i++;
				}
			}
		}


	}

	int QuadNode::GetIndex(Rect rect)
	{
		int index = -1;
		if (rect.left < this->bounds.right && rect.right < this->bounds.right)
		{
			if (rect.top < this->bounds.bottom && rect.bottom < this->bounds.bottom)
			{
				index = 1;
			}
			else if (rect.top > this->bounds.bottom)
			{
				index = 2;
			}
		}
		else if (rect.left > this->bounds.right)
		{
			if (rect.top < this->bounds.bottom && rect.bottom < this->bounds.bottom)
			{
				index = 0;
			}
			else if (rect.top > this->bounds.bottom)
			{
				index = 3;
			}
		}

		return index;
	}

	void QuadNode::Retrieve(std::list<Body*>* retrieveList, Rect source)
	{
		retrieveList->insert(retrieveList->end(), this->objects.begin(), this->objects.end());

		int index = this->GetIndex(source);

		if (this->nodes.size() > 0)
		{
			if (index !=  -1)
			{
				this->nodes[index]->Retrieve(retrieveList, source);
			}
			else
			{
				this->nodes[0]->Retrieve(retrieveList, source);
				this->nodes[1]->Retrieve(retrieveList, source);
				this->nodes[2]->Retrieve(retrieveList, source);
				this->nodes[3]->Retrieve(retrieveList, source);
			}
		}
	}

	void QuadNode::Clear()
	{
		this->objects.clear();

		for (auto it = this->nodes.begin(); it != this->nodes.end(); ++it) {
			(*it)->Clear();
			delete (*it);
		}

		this->nodes.clear();
	}

	void QuadNode::InsertFromDrawList(std::list<GameObject*> drawList)
	{
		for (auto it = drawList.begin(); it != drawList.end(); ++it) {
			if ((*it)->body != nullptr) {
				this->Insert((*it)->body);
			}
		}
	}

}
