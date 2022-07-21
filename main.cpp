#include <iostream>
#include <vector>
#include <memory>

struct Node
{
    int data;
    std::shared_ptr<Node> node1;
    std::shared_ptr<Node> node2;
    Node() {}
    Node(int n) : data(n) {}
};

void printList(std::shared_ptr<Node> root)
{
    while(root)
    {
        std::cout << root->data << ' ';
        root = root->node2;
    }
}

void makeOrder(std::shared_ptr<Node> curRoot, std::shared_ptr<Node>& curHead)
{
    if(curRoot == nullptr) return;

    if(curRoot->node1)
        makeOrder(curRoot->node1, curHead);

    if(curHead != nullptr)
    {
        curHead->node2 = curRoot;
        curRoot->node1 = curHead;
    }

    curHead = curRoot;

    if(curRoot->node2)
        makeOrder(curRoot->node2, curHead);
}

std::shared_ptr<Node> makeLinkedList(Node root)
{
    std::shared_ptr<Node> curNode = std::make_shared<Node>(root);
    std::shared_ptr<Node> head;

    makeOrder(curNode, head);

    while(head->node1)
        head = head->node1;

    return head;
}

int main()
{
    Node root(10);
    root.node1 = std::make_shared<Node>(12);
    root.node2 = std::make_shared<Node>(15);
    root.node1->node1 = std::make_shared<Node>(25);
    root.node1->node2 = std::make_shared<Node>(30);
    root.node2->node1 = std::make_shared<Node>(36);
    root.node2->node2 = std::make_shared<Node>(40);
    printList(makeLinkedList(root));
    return 0;
}
