class Item {
    public:
        Item();
        ~Item();
        void setId(int id);
        void setQuantity(int quantity);
        void setName(string name);
        int getId() const;
        int getQuantity() const;
        string getName() const;
        void read();
        void write();
    private:
        int id;
        int qty;
        int lenName; //calculated (no setter/getter)
        string name;
}