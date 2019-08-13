#include <iostream>
#include <ostream>

using namespace std;

// Leetcode's definition for singly-linked list.
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
	/*

	Adds a new number to a given linked list.
	Returns a pointer of the new node added to the linked list
	
	*/
	ListNode* addNumberToList(ListNode** head, int num)
	{
		// The new node we want to add to linked list
		ListNode* temp = new ListNode(num);

		// Iterator for traversing the linked list
		ListNode* itr = *head;

		// If linked list is empty, set the head to our new node.
		if (*head == NULL)
		{
			*head = temp;
			return *head;
		}

		// Traverse the list until we reach the final node.
		while (itr->next != NULL)
		{
			itr = itr->next;
		}

		// Set ire->next to our new node and return pointer to new node
		itr->next = temp;
		return itr->next;
	}

	/*
	
	Makes the given linked lists have the same size.
	Side-effect: Modifies the original lists.
	
	*/
	void preprocessLists(ListNode** l1, ListNode** l2)
	{
		// Iterators dedicated to each list
		ListNode* itrL1 = *l1;
		ListNode* itrL2 = *l2;

		// Iterate through each list until both iterators are NULL
		while (itrL1 != itrL2)
		{
			if (itrL1 == NULL)
			{
				itrL1 = addNumberToList(l1, 0);
			}
			else if (itrL2 == NULL)
			{
				itrL2 = addNumberToList(l2, 0);
			}
			else
			{
				itrL1 = itrL1->next;
				itrL2 = itrL2->next;
			}
		}
	}

public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

		// Preprocess the lists
		preprocessLists(&l1, &l2);

		// Initalize an iterator for each linked list
		ListNode* itrL1 = l1;
		ListNode* itrL2 = l2;

		// Initalize our result linked list.
		ListNode* result = NULL;

		// Traverse through the two lists until the end it hit
		while (itrL1 != NULL && itrL2 != NULL)
		{
			// The sum of the two numbers in each list
			int sum = itrL1->val + itrL2->val;

			// We need to check if our sum is greater than or equal to 10.
			if (sum >= 10)
			{
				// This will go in place of the two digit number
				int difference = sum - 10;
				// This will be the 1 in two digit number
				int remainder = 1;

				// Check if there is room to add our remainder
				if (itrL1->next == NULL && itrL2->next == NULL)
				{
					addNumberToList(&itrL1, remainder);
					addNumberToList(&itrL2, 0);
					addNumberToList(&result, difference);
				}
				else if (itrL1->next == NULL && itrL2->next != NULL)
				{
					addNumberToList(&itrL1, remainder);
					addNumberToList(&result, difference);
				}
				else if (itrL1->next != NULL && itrL2->next == NULL)
				{
					addNumberToList(&itrL2, 0);
					itrL1->next->val += remainder;
					addNumberToList(&result, difference);
				}
				else
				{
					itrL1->next->val += remainder;
					addNumberToList(&result, difference);
				}
			}
			else
			{
				addNumberToList(&result, sum);
			}

			// Progress forward in both lists
			itrL1 = itrL1->next;
			itrL2 = itrL2->next;
		}

		return result;
	}
};

// Used for debugging
ostream& operator<<(ostream& os, ListNode* head)
{
	ListNode* itr = head;

	while (itr != NULL)
	{
		os << itr->val;

		if (itr->next != NULL)
		{
			os << " -> ";
		}

		itr = itr->next;
	}

	return os;
}
