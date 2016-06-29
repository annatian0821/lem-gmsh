#ifdef READMESH_ELEMENTS
#define READMESH_ELEMENTS

#include <vector>

// Element class
// \brief Element for associating elements with surfaces and vertices   

class Elements {
 public: 

 // Constructor with element id 
 explicit Elements(const unsigned eid) : eid_{eid} {
   s_list_.clear();
   v_list_.clear();
 }
 
 // Assigm list of surfaces to the element 
 void s_list(const std::vector<unsigned>& s_list) {s_list_ = s_list;}

 // Assign list of vertices to the element 
 void v_list(const std::vector<unsigned>& v_list) {v_list_ = v_list;}

 // Return id of the element 
 unsigned eid() const {return eid_;}

 // Return list of surfaces for a given element
 std::vector<unsigned> s_list(const unsigned eid) const {return s_list_; }

 // Return list of vertices for a given element
 std::vector<unsigned> v_list(const unsigned eid) const {return v_list_; }

 private:  
 unsigned eid_; 
 std::vector<unsigned> s_list_; 
 std::vector<unsigned> v_list_; 

};

#endif // READMESH_ELEMENTS
