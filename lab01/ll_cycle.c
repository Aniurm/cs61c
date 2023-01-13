#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    node* fast = head, *slow = head;
    do {
        if (fast == NULL || fast->next == NULL) {
            return 0;
        }
        fast = fast->next->next;
        slow = slow->next;
    } while (slow != fast);
    return 1;
}