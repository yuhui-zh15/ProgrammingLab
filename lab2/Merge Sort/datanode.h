#ifndef DATANODE_H
#define DATANODE_H

struct dataNode
{
int key;
int val;
struct dataNode * next;
dataNode()
{
    next = NULL;
}
};

#endif // DATANODE_H