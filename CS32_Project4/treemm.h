#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>
#include <iostream>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    struct Node;
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            m_nPtr = nullptr; // sets private node to nullptr
            index = 0;
        }
        
        Iterator(Node* n) {
            m_nPtr = n;
            index = 0;
        }

        ValueType& get_value() const
        {
            return (m_nPtr->m_values[index]);  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            if (m_nPtr != nullptr && index < m_nPtr->m_values.size()) { // valid if index and pointer are valid
                return(true);
            }
            else {
                return(false);
            }
            
        }

        void advance()
        {
            index = index + 1;
        }
      private:
        Node* m_nPtr;
        int index;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        deleteNodes(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        insertion(m_root, key, value);
    }

    Iterator find(const KeyType& key) const
    {
        Node* temp = m_root;
        while (temp != nullptr) { // go through while you don't hit a null node
            if (key == temp->m_key) {
                return(Iterator(temp));
            }
            else if (key < (temp->m_key)) {
                temp = temp->m_left;
            }
            else if (key > (temp->m_key)) {
                temp = temp->m_right;
            }
        }
        
        return(Iterator());
    }

  private:
    struct Node {
        Node* m_left = nullptr;
        Node* m_right = nullptr;
        std::vector<ValueType> m_values;
        KeyType m_key;
    };
    
    Node* m_root;
    
    void insertion(Node* &node, KeyType key, ValueType value) { //
        if (node == nullptr) {
            node = new Node;
            node->m_key = key;
            node->m_values.push_back(value);
            return;
        }
        
        if (key == node->m_key) // found same key so insert value if possible and return
        {
            
            Iterator it(node);
            
            while(it.is_valid())
            {
                if(it.get_value() == value)
                    return;
                
                it.advance();
            }
            
            node->m_values.push_back(value); // add value to vector
            return;
        }
        else if (key < node->m_key) {
            if (node->m_left == nullptr) { // if there is a nullptr to the left available insert
                Node* n = new Node;
                node->m_left = n;
                n->m_key = key;
                n->m_values.push_back(value);
                return;
            }
            insertion(node->m_left, key, value);
        }
        else if (key > node->m_key) {
            if (node->m_right == nullptr) {
                Node* n = new Node;
                node->m_right = n;
                n->m_key = key;
                n->m_values.push_back(value);
                return;
            }
            insertion(node->m_right, key, value);
        }
    }
    
    void deleteNodes(Node* root) {
        
        if (root == nullptr) {
            return;
        }
        
        deleteNodes(root->m_right); // recursively calls function to delete through backtracking
        deleteNodes(root->m_left);
        
        delete root;
    }
};


#endif // TREEMULTIMAP_INCLUDED
