template <typename T>
class Searcher {
   public:
    void search() {
        static_cast<T*>(this)->search();
    }
};