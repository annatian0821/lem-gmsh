#ifdef READMESH_ELEMENT
#define READMESH_ELEMENT

#include <vector>

// Element class
// \brief Element for  

class Element {
 public: 


 private:  
 unsigned sid_; 
 std::vector<unsigned> s_list_; 
 std::vector<unsigned> vid_list_; 

};

#endif // READMESH_ELEMENT

