#include <iostream>
using namespace std;

struct listNode
{
    int val;
    listNode *next;
    listNode() : val(0), next(nullptr) {}
    listNode(int x) : val(x), next(nullptr) {}
    listNode(int x, listNode *next) : val(x), next(next) {}
};

// EFFECTS: Read in formatted input and return the head pointer of link list
listNode *inputList()
{
    // DO NOT MODIFY THIS PART
    int n, tmp;
    cin >> n;
    cin >> tmp;
    listNode *head = new listNode(tmp);
    listNode *prev = head;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> tmp;
        listNode *newNode = new listNode(tmp);
        prev->next = newNode;
        prev = newNode;
    }
    return head;
}

// EFFECTS: Print the link list with given head pointer
void printList(listNode *head)
{
    // DO NOT MODIFY THIS PART
    listNode *tmp = head;
    while (tmp)
    {
        cout << tmp->val << ' ';
        tmp = tmp->next;
    }
    cout << endl;
}

// EFFECTS: split link list into left and right
void split(listNode *head, listNode **left, listNode **right)
{
    listNode *fast;
    listNode *slow;
    slow = head;
    fast = head->next;
    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

// EFFECTS: merge two linked lists
listNode *merge(listNode *left, listNode *right)
{
    listNode *out = nullptr;
    // base
    if (left == nullptr)
    {
        return right;
    }
    else if (right == nullptr)
    {
        return left;
    }
    // compare and merge
    if (left->val <= right->val)
    {
        out = left;
        out->next = merge(left->next, right);
    }
    else if (right->val <= left->val)
    {
        out = right;
        out->next = merge(left, right->next);
    }
    return out;
}

// EFFECTS: return sorted link list
listNode *listSort(listNode *head)
{
    // merge sort
    // base
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    listNode *left;
    listNode *right;
    split(head, &left, &right);
    left = listSort(left);
    right = listSort(right);
    head = merge(left, right);
    return head;
}

// EFFECTS: delete allocated memory
void deleteList(listNode *head)
{
    // DO NOT MODIFY THIS PART
    while (head)
    {
        listNode *tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main()
{
    // DO NOT MODIFY THIS PART
    listNode *head = inputList();
    head = listSort(head);
    printList(head);
    deleteList(head);
    return 0;
}