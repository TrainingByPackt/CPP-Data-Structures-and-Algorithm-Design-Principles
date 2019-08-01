#include <iostream>
#include <queue>

struct node
{
    std::string name;
    node *first, *second;
};

struct family_tree
{
    node *root;

    static family_tree create_family(const std::string &name)
    {
        family_tree family;
        family.root = new node{name, NULL, NULL};
        return family;
    }

    static node *find(node *root, const std::string &value)
    {
        if (root == NULL)
            return NULL;
        if (root->name == value)
            return root;
        auto firstFound = family_tree::find(root->first, value);
        if (firstFound != NULL)
            return firstFound;
        return family_tree::find(root->second, value);
    }

    bool addChild(const std::string &father, const std::string &son)
    {
        auto fatherNode = family_tree::find(root, father);
        if (not fatherNode)
        {
            std::cout << "No person named " << father << std::endl;
            return false;
        }
        if (fatherNode->first && fatherNode->second)
        {
            std::cout << father << " already has 2 sons." << std::endl;
            return false;
        }
        if (not fatherNode->first)
            fatherNode->first = new node{son, NULL, NULL};
        else
            fatherNode->second = new node{son, NULL, NULL};
        return true;
    }

    static void preOrder(node *start)
    {
        if (not start)
            return;
        std::cout << start->name << " ";
        preOrder(start->first);
        preOrder(start->second);
    }

    static void inOrder(node *start)
    {
        if (not start)
            return;
        inOrder(start->first);
        std::cout << start->name << " ";
        inOrder(start->second);
    }
};

int main()
{
    auto tree = family_tree::create_family("Shantanu");
    if (tree.addChild("Shantanu", "Bhishma"))
        std::cout << "Added Bhishma in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Bhishma in the tree" << std::endl;

    if (tree.addChild("Shantanu", "Vyaas"))
        std::cout << "Added Vyaas in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Vyaas in the tree" << std::endl;

    if (tree.addChild("Vyaas", "Dhrishtra"))
        std::cout << "Added Dhrishtra in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Dhrishtra in the tree" << std::endl;

    if (tree.addChild("Vyaas", "Pandu"))
        std::cout << "Added Pandu in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Pandu in the tree" << std::endl;

    if (tree.addChild("Pandu", "Arjun"))
        std::cout << "Added Arjun in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Arjun in the tree" << std::endl;

    if (tree.addChild("Pandu", "Yudhishthir"))
        std::cout << "Added Yudhishthir in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Yudhishthir in the tree" << std::endl;

    if (tree.addChild("Pandu", "Bhima"))
        std::cout << "Added Bhima in the tree." << std::endl;
    else
        std::cout << "Couldn’t add Bhima in the tree" << std::endl;

    std::cout << "Preorder:\t";
    family_tree::preOrder(tree.root);
    std::cout << std::endl;

    std::cout << "Inorder:\t";
    family_tree::inOrder(tree.root);
    std::cout << std::endl;
}
