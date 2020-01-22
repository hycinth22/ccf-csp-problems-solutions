struct mylogType {
#ifdef     _DEBUG
    static constexpr const bool debug = true;
#else
    static constexpr const bool debug = false;
#endif
    ostream& os;
    mylogType(ostream& os) : os(os) {}
    template<class contentType>
    mylogType &operator<<(const contentType &cont) {
        if (debug) {
            os << cont;
        }
        return *this;
    }
    mylogType &operator<<(ostream &op(ostream &)) {
        if (debug) {
            op(os);
        }
        return *this;
    }
} mylog(clog);