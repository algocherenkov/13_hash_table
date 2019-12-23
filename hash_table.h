#pragma once
#include <type_traits>
#include <vector>
#include <memory>
#include <cassert>

namespace otus {

constexpr int BUFF_LENGTH = 5;
constexpr int CHAIN_THRESHOLD = 10;

template<typename Key, typename Value, typename Enable = void>
class HashTable;

template<typename Key, typename Value>
class HashTable<Key, Value, typename std::enable_if<std::is_integral<Key>::value >::type>
{
public:
    HashTable()
    {
        m_buff.resize(BUFF_LENGTH, nullptr);
    }

private:
    struct NodeData {
        NodeData(Key& k, Value& v):
            key(k),
            value(v)
        {}

        Key key;
        Value value;
    };

    struct Node
    {
        Node(Key& k, Value& v):
            data_(k, v)
        {
            size_++;
        }

        void push(Key k, Value& v) {
            if(size_ == 1) {
                next_ = new Node(k,v);
                size_++;
                return;
            } else if (size_ < CHAIN_THRESHOLD) {
                Node* temp = next_;
                for(size_t i = 1; i < size_ - 1; i++)
                    temp = temp->next_;
                temp->next_ = new Node(k,v);
                size_++;
                return;
            }
            if(!rebuilded)
                rebuildToBST();

            insert(data_.key < k? left_: right_, new Node(k, v));

            size_++;
        }

        Value& get(Key k)
        {
            if(size_ == 1)
                return data_.value;
            else if(size_ < CHAIN_THRESHOLD)
            {
                Node* temp = next_;
                for(size_t i = 1; i < size_; i++)
                {
                    if(temp->data_.key == k)
                        return temp->data_.value;
                    temp = temp->next_;
                }
            } else {
                auto result = search(this, k);
                return result->data_.value;
            }
        }
    private:
        void rebuildToBST(){
            Node* temp = next_;

            for(size_t i = 1; i < size_; i++)
            {
                insert(this, temp);
                temp = temp->next_;
            }
            rebuilded = true;
        }

        Node* insert(Node* node, Node* item)
        {
            if (node == nullptr) return item;

            if (item->data_.key < node->data_.key)
                node->left_  = insert(node->left_, item);
            else if (item->data_.key > node->data_.key)
                node->right_ = insert(node->right_, item);

            return node;
        }

        Node* search(Node* root, Key key)
        {
            if (root == nullptr || root->data_.key == key)
               return root;

            if (root->data_.key < key)
               return search(root->right_, key);

            return search(root->left_, key);
        }

        Node* next_{nullptr};
        Node* left_{nullptr};
        Node* right_{nullptr};
        NodeData data_;
        int size_{0};
        bool rebuilded {false};
    };

public:
    void push(Key key, Value value){
        int pos = hash(key);

        if(!m_buff[pos])
        {
            m_buff[pos] = std::make_shared<Node>(key, value);
            return;
        }

        m_buff[pos]->push(key, value);
    }

    Value& get(Key key) {
        int pos = hash(key);

        if(m_buff[pos])
            return m_buff[pos]->get(key);
        else
            assert(false);
    }

private:
    int hash(Key& key) {
        return key % BUFF_LENGTH;
    }

private:
    std::vector<std::shared_ptr<Node>> m_buff;
};

}
