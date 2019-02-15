template<typename Data>
class Vector {
  size_t d_size; // Stores no. of actually stored objects
  size_t d_capacity; // Stores allocated capacity
  Data *d_data; // Stores data
  public:
    Vector() : d_size(0), d_capacity(0), d_data(0) {
      d_data = NULL;
      resize();
    };
    
    Vector(Vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) {
      d_data = (Data *)malloc(d_capacity*sizeof(Data));
      memcpy(d_data, other.d_data, d_size*sizeof(Data));
    }; // Copy constuctor
    
    ~Vector() {
      if(d_data != NULL) free(d_data);
    }; // Destructor
    
    Vector &operator=(Vector const &other) {
      if(d_data != NULL) free(d_data); 
      d_size = other.d_size; 
      d_capacity = other.d_capacity; 
      d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
      memcpy(d_data, other.d_data, d_size*sizeof(Data));
      return *this;
    };
    
    void push_back(Data const &x) {
      if (d_capacity == d_size) 
        resize(); 
      d_data[d_size++] = x;
    }; // Adds new value. If needed, allocates more space
    
    size_t size() const {
      return d_size;
    }; // Size getter

    Data dummyData;

    Data &front() {
      return d_data != NULL ? d_data[0] : dummyData;
    };
    
    Data &back() {
      return d_data != NULL ? d_data[d_size - 1] : dummyData;
    };

    boolean remove(size_t idx) {
      if(d_data == NULL || idx >= d_size || d_size == 0)
        return false;
      if(idx == d_size - 1) {
        d_data[idx] = NULL;  
      } else {
        for(int i = idx; i < d_size - 1; i++) {
          d_data[i] = d_data[i+1];
        }
        d_data[d_size - 1] = NULL;
      }
      d_size--;
      return true;
    };
    
    Data const &operator[](size_t idx) const {
      return d_data == NULL || d_size <= idx ? dummyData : d_data[idx];
    }; // Const getter
    
    Data &operator[](size_t idx) {
      return d_data == NULL || d_size <= idx ? dummyData : d_data[idx];
    };
    
private:
  void resize() {
    d_capacity = d_capacity ? d_capacity * 2 : 10;
    Data *newdata = (Data *)malloc(d_capacity*sizeof(Data));
    if(d_data != NULL) {
      memcpy(newdata, d_data, d_size * sizeof(Data));
      free(d_data);        
    }
    d_data = newdata;
  };
};
