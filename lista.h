#ifndef LISTA
#define LISTA

/*
   pel_list.hpp
   -----------------------------------
   Doubly-linked circular list
   -----------------------------------
   PEL - UEM - 2014/2015 Academic Year
   -----------------------------------
   v3.0 - May 26, 2015
*/


#include <cstddef> // to be able to use std::size_t
#include <initializer_list>
#include <utility> // to be able to use std::swap

namespace pel {

////////////////////////////////////////////////////////////////////////////////
// implementation details:

namespace detail {

struct NodeBase {
   NodeBase* prev, // previous node
           * next; // succesor node

   void hook(NodeBase* b) noexcept // place this node in front of b
   {
      next = b;
      prev = b->prev;
      b->prev = b->prev->next = this;
   }

   void unhook() noexcept // isolate this node
   {
      prev->next = next;
      next->prev = prev;
      next = prev = this;
   }

   void swap(NodeBase& b)  noexcept // exchange this node and b
   {
      if (next != this) { // this node is not isolated...
         if (b.next != &b) { // ...and neither is b
            std::swap(next,b.next);
            std::swap(prev,b.prev);
            next->prev = prev->next = this;
            b.next->prev = b.prev->next = &b;
         }
         else { // ...but b is isolated
            b.next = next;
            b.prev = prev;
            b.next->prev = b.prev->next = &b;
            next = prev = this;
         }
      }
      else if (b.next != &b) { // this node is isolated, b is not
         next = b.next;
         prev = b.prev;
         next->prev = prev->next = this;
         b.next = b.prev = &b;
      }
   }

   // move [first,last) before this node
   void transfer(NodeBase* first, NodeBase* last) noexcept
   {
      if (this == last)
         return;

      auto tmp = last->prev;
      // remove [first,last) from its old position and splice it into its
      // new position
      first->prev->next = last;
      last->prev->next = this;
      last->prev = first->prev;

      first->prev = prev;
      prev->next = first;
      prev = tmp;
   }
};

} // detail NAMESPACE

////////////////////////////////////////////////////////////////////////////////

template<typename T> // T must be a type
class List {

   struct Node : detail::NodeBase { // public inheritance
      T data; // stored value
      Node(T const& d) : data(d) { };
   };

   detail::NodeBase dnb_; // dummy NodeBase

public:

   struct ListIterator; // see definition below
   struct ListConstIterator;

   /////////////////////////////////////////////////////////////////////////////
   // construction/copy/destruction:

   List() noexcept  // create an empty list
      : dnb_{&dnb_,&dnb_} { } // default constructor (class invariant)

   List(std::initializer_list<T> const& list)
      : dnb_{&dnb_,&dnb_}
   {
     try {
         for (auto const& val : list)
            pushBack(val);
      }
      catch (...) {
         clear();
         throw;
      }
   }

   List(List<T> const& list) // copy constructor
      : dnb_{&dnb_,&dnb_}
   {
      try {
         for (auto const& val : list)
            pushBack(val);
      }
      catch (...) {
         clear();
         throw;
      }
   }

   List<T>& operator=(List<T> const& list) // copy assignment operator
   {
      // copy and swap idiom (strong exception safety guarantee):
      List<T> tmp{list};
      dnb_.swap(tmp.dnb_);
      return *this;
   } // tmp is automatically destroyed here

   ~List() { clear(); }

   /////////////////////////////////////////////////////////////////////////////
   // element access:

   T&       front()       { return *begin(); } // access the first element
   T const& front() const { return *begin(); }

   T&       back()       { return *(--end()); } // access the last element
   T const& back() const { return *(--end()); }

   /////////////////////////////////////////////////////////////////////////////
   // modifiers:

   void popFront() noexcept { erase(begin()); }
   void popBack()  noexcept { erase(ListIterator{dnb_.prev}); }

   void pushFront(T const& val) { insert(begin(),val); }
   void pushBack(T const& val)  { insert(ListIterator{&dnb_},val); }

   void insert(ListIterator position, T const& val) // strong safety guarantee
   {
      Node* p = new Node{val};
      p->hook(position.node);
   }

   void insert(ListIterator position, std::initializer_list<T> const& list)
   {
      if (!list.count())
         return;

      List<T> tmp{list};
      position.node->transfer(tmp.begin().node,tmp.end().node);
   }

   ListIterator erase(ListIterator position) noexcept
   {
      ListIterator ret{position.node->next};
      position.node->unhook();
      delete static_cast<Node*>(position.node); // safe downcasting
      return ret;
   }

   void clear() noexcept
   {
      auto current = dnb_.next;
      while (current != &dnb_) {
         auto tmp = current;
         current = current->next;
         delete static_cast<Node*>(tmp); // safe downcasting
      }
      dnb_.next = dnb_.prev = &dnb_;
   }

   /////////////////////////////////////////////////////////////////////////////
   // capacity:

   std::size_t count() const noexcept
   {
      std::size_t sz = 0;
      auto p = dnb_.next;
      while (p != &dnb_) {
         ++sz;
         p = p->next;
      }
      return sz;
   }

   T const at(size_t it) {
       auto iter=begin();
       for (size_t i=0; i<it; i++){
           ++iter;
       }
       return *iter;
   }

   void append(T const& val)  { insert(ListIterator{&dnb_},val); }

   void replace (ListIterator position, T const& nuevo){
       *position = nuevo;
   }

   void replace (int position, T const& nuevo){
       auto iter = this->begin();
       for (int i=0; i<position; i++){
           iter++;
       }
       replace(iter,nuevo);
   }

   bool empty() const noexcept { return dnb_.next == &dnb_; }

   /////////////////////////////////////////////////////////////////////////////
   // iterators:

   ListConstIterator begin() const noexcept { return ListConstIterator{dnb_.next}; }
   ListIterator      begin()       noexcept { return ListIterator{dnb_.next}; }

   ListConstIterator end() const noexcept { return ListConstIterator{&dnb_}; }
   ListIterator      end()       noexcept { return ListIterator{&dnb_}; }

   /////////////////////////////////////////////////////////////////////////////

   struct ListIterator {
      detail::NodeBase* node;

      explicit ListIterator(detail::NodeBase* node_ = nullptr) noexcept
         : node{node_} { }

      bool operator==(ListIterator const& rhs) const noexcept { return node == rhs.node; }
      bool operator!=(ListIterator const& rhs) const noexcept { return node != rhs.node; }

      T& operator*() const
      {
         return static_cast<Node*>(node)->data; // safe downcasting
      }
      T* operator->() const noexcept
      {
         return &(static_cast<Node*>(node)->data); // idem
      }

      ListIterator& operator++() noexcept // prefix
      {
         node = node->next;
         return *this;
      }
      ListIterator operator++(int) noexcept // postfix
      {
         auto tmp = *this;
         node = node->next;
         return tmp;
      }
      ListIterator& operator--() noexcept // prefix
      {
         node = node->prev;
         return *this;
      }
      ListIterator operator--(int) noexcept // postfix
      {
         auto tmp = *this;
         node = node->prev;
         return tmp;
      }
   };

   struct ListConstIterator {
      detail::NodeBase const* node;

      explicit ListConstIterator(detail::NodeBase const* node_ = nullptr) noexcept
         : node{node_} { }

      bool operator==(ListConstIterator const& rhs) const noexcept { return node == rhs.node; }
      bool operator!=(ListConstIterator const& rhs) const noexcept { return node != rhs.node; }

      T const& operator*() const
      {
         return static_cast<Node const*>(node)->data; // safe downcasting
      }
      T const* operator->() const noexcept
      {
         return &(static_cast<Node const*>(node)->data); // idem
      }

      ListConstIterator& operator++() noexcept
      {
         node = node->next;
         return *this;
      }
      ListConstIterator operator++(int) noexcept
      {
         auto tmp = *this;
         node = node->next;
         return tmp;
      }
      ListConstIterator& operator--() noexcept
      {
         node = node->prev;
         return *this;
      }
      ListConstIterator operator--(int) noexcept
      {
         auto tmp = *this;
         node = node->prev;
         return tmp;
      }
   };
};

} // pel NAMESPACE


#endif // LISTA

