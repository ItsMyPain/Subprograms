#include <iostream>
#include <cassert>
using namespace std;

struct subset_node
{
  int key;
  subset_node* left;
  subset_node* right;
  subset_node* parent;
};

bool init(subset_node** sn)
{
  *sn = NULL;
  return true;
}

bool insert(subset_node** sn, int k, subset_node* parent = NULL)
{
  if ((*sn) == NULL)
  {
    *sn = new subset_node;
    (*sn)->key = k;
    (*sn)->left = NULL;
    (*sn)->right = NULL;
    (*sn)->parent = parent;
    if (parent)
    {
      if ((*sn)->key > parent->key)
        parent->right = *sn;
      else
        parent->left = *sn;
    }
    return true;
  }
  if (k < (*sn)->key)
    return insert(&((*sn)->left), k, *sn);
  else if (k > (*sn)->key)
    return insert(&((*sn)->right), k, *sn);
  return false;
}

unsigned int size(subset_node* sn)
{
  if (sn == NULL)
    return 0;
  return (1 + size(sn->left) + size(sn->right));
}

unsigned int height(subset_node* sn)
{
  if (sn == NULL)
    return 0;
  return (1 + max(size(sn->right), size(sn->left)));
}

void destructor(subset_node* sn)
{
  if (sn == NULL)
    return;
  destructor((*sn).left);
  destructor((*sn).right);

  delete sn;
  sn = NULL;

  return;
}

subset_node* find(subset_node* sn, int k)
{
  if (sn == NULL)
    return NULL;
  if ((*sn).key == k)
    return sn;
  if ((*sn).key < k)
    return find((*sn).right, k);
  else
    return find((*sn).left, k);
}

subset_node* FM(subset_node* sn)
{
  if (sn->left == NULL)
    return sn;
  subset_node * min = sn;
  while (min->left)
    min = min->left;
  return min;
}

subset_node* RC(subset_node* sn, int k)
{
    if (sn == NULL)
      return sn;
    if (k < sn->key)
      sn->left = RC(sn->left, k);
    else
        if (k > sn->key)
            sn->right = RC(sn->right, k);
        else
            if (sn->left != NULL && sn->right != NULL)
            {
              sn->key = FM(sn->right)->key;
              sn->right = RC(sn->right, sn->key);
            }
            else
            {
              subset_node * tmp = sn;
              if (sn->left != NULL)
                sn = sn->left;
              else
                if (sn->right != NULL)
                    sn = sn->right;
                else
                    sn = NULL;
              delete tmp;
            }
            return sn;
}

bool remove(subset_node** sn, int k)
{
  *sn = RC(*sn, k);
  return true;
}

void DFSH(subset_node* sn, int* arr, int* i)
{
  if (sn == NULL)
    return;

  DFSH(sn->left, arr, i);
  arr[*i] = sn->key;
  (*i)++;
  DFSH(sn->right, arr, i);
  return;
}

int* DFS(subset_node* sn)
{
  size_t size_arr = size(sn);
  int* arr = new int [size_arr];
  int i = 0;
  DFSH(sn, arr, &i);
  return arr;
}


