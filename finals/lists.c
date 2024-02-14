static void insertList(List newList, int value) { 
        if (newList = NULL) { 
                newList->value = value;
        } else { 
                while (newList->next != NULL) { 
                        newList = newList->next;
                }
                newList->next->value = value;
        }
}