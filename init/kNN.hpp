#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void getArray(T *array) const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    virtual List<T> *subList(int start, int end) = 0;
    virtual void supPrint(int start, int end) const = 0;
};

template <typename T>
class SupList : public List<T>
{
private:
    class Node
    {
    public:
        T data;
        Node *next;

    public:
        Node(T data, Node *next = nullptr) : data(data), next(next) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

public:
    SupList()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~SupList()
    {
        this->clear();
    }
    void push_back(T value)
    {
        Node *newnode = new Node(value, nullptr);
        if (size == 0)
        {
            head = newnode;
            tail = head;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
        }
        size++;
    }
    void push_front(T value)
    {
        Node *newnode = new Node(value, nullptr);
        if (size == 0)
        {
            head = newnode;
            tail = head;
        }
        else
        {
            newnode->next = head;
            head = newnode;
        }
        size++;
    }
    void insert(int index, T value)
    {
        if (index < 0 || index > this->size)
            return;
        else if (index == 0)
        {
            push_front(value);
        }
        else if (index == this->size || this->size == 0)
        {
            push_back(value);
        }
        else
        {
            Node *newnode = new Node(value, nullptr);
            Node *temp = head;
            index--;
            while (index)
            {
                temp = temp->next;
                index--;
            }
            newnode->next = temp->next;
            temp->next = newnode;
            size++;
        }
    }
    void remove(int index)
    {
        if (index < 0 || index >= size)
            return;
        else if (size == 0)
            return;
        else if (index == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node *temp = head;
            index--;
            while (index)
            {
                temp = temp->next;
                index--;
            }
            if (temp->next->next)
            {
                Node *d = temp->next;
                temp->next = temp->next->next;
                delete d;
            }
            else
            {
                tail = temp;
                Node *d = temp->next;
                temp->next = nullptr;
                delete d;
            }
        }
        size--;
    }
    T &get(int index) const
    {
        if (index < 0 || index >= this->size) throw std::out_of_range("get(): Out of range");
        Node *temp = head;
        while (index != 0)
        {
            temp = temp->next;
            index--;
        }
        return temp->data;
    }
    int length() const
    {
        return size;
    }
    void getArray(T *array) const
    {
        if (this->size == 0)
            return;
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            array[i] = temp->data;
            temp = temp->next;
        }
        delete temp;
    }
    void clear()
    {
        Node *temp = head;
        while (temp)
        {
            temp = temp->next;
            delete head;
            head = temp;
        }
        tail = head = nullptr;
        size = 0;
    }

    void print() const
    {
        if ( this->size == 0 ) return;        
        Node *temp = head;
        for (int i = 0; i < this->size; i++)
        {
            if (i == this->size - 1)
                cout << temp->data;
            else
            {
                cout << temp->data << " ";
            }
            temp = temp->next;
        }
    }
    void reverse()
    {
        if (this->size == 0 || this->size == 1)
            return;
        else
        {
            Node *now = head;
            Node *after = head->next;
            Node *savenode;
            int i = this->size - 1;
            while (i--)
            {
                savenode = after->next;
                after->next = now;
                now = after;
                after = savenode;
            }
            head->next = nullptr;
            tail = head;
            head = now;
        }
    }
    void supPrint(int start, int end) const
    {
        Node *temp = head;
        for (int i = 0; i < start; i++)
            temp = temp->next;
        for (int i = start; i < end && i < this->size; i++)
        {
            if (i == end - 1 || i == this->size - 1)
                cout << temp->data;
            else
            {
                cout << temp->data << " ";
            }
            temp = temp->next;
        }
    }
    List<T> *subList(int start, int end)
    {
        List<T> *result = new SupList<T>;
        if (this->size <= start)
            return result;
        if (start < 0 || end < start)
            return result;
        if (end >= this->size)
        {
            Node *temp = this->head;
            if (start != 0)
            {
                while (start)
                {
                    temp = temp->next;
                    start--;
                }
            }
            while (temp)
            {
                result->push_back(temp->data);
                temp = temp->next;
            }
        }
        else
        {
            Node *temp = this->head;
            int a = start;
            if (a != 0)
            {
                while (a)
                {
                    temp = temp->next;
                    a--;
                }
            }
            while (end > start)
            {
                result->push_back(temp->data);
                temp = temp->next;
                end--;
            }
        }
        return result;
    }
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameCol;
    // You may need to define more
public:
    Dataset()
    {
        this->nameCol = new SupList<string>;
        this->data = new SupList<List<int> *>;
    }
    ~Dataset()
    {
        for (int i = 0; i < this->data->length(); i++)
        {
            delete this->data->get(i);
        }

        delete data;
        delete nameCol;
    }
    Dataset(const Dataset &other)
    {
        this->nameCol = new SupList<string>;
        this->data = new SupList<List<int> *>;
        for (int i = 0; i < other.nameCol->length(); i++)
        {
            this->nameCol->push_back(other.nameCol->get(i));
        }
        if (other.data->length() == 0)
            return;
        int numcol = max(this->nameCol->length(), other.data->get(0)->length());
        for (int i = 0; i < other.data->length(); i++)
        {
            this->data->push_back(other.data->get(i)->subList(0, numcol));
        }
    }
    Dataset &operator=(const Dataset &other)
    {
        if (this == &other)
            return *this;
        this->~Dataset();
        this->nameCol = new SupList<string>;
        this->data = new SupList<List<int> *>;
        for (int i = 0; i < other.nameCol->length(); i++)
        {
            this->nameCol->push_back(other.nameCol->get(i));
        }
        if (other.data->length() == 0)
            return *this;
        int numcol = max(this->nameCol->length(), other.data->get(0)->length());
        for (int i = 0; i < other.data->length(); i++)
        {
            this->data->push_back(other.data->get(i)->subList(0, numcol));
        }
        return *this;
    }
    bool loadFromCSV(const char *fileName)
    {
        ifstream f(fileName);
        if (f.is_open())
        {
            string str;
            f >> str;
            unsigned int i = 0;
            while (i < str.length())
            {
                if (str[i] == ',')
                    str[i] = ' ';
                i++;
            }
            stringstream ss(str);
            while (ss >> str)
            {
                nameCol->push_back(str);
            }

            while (f >> str)
            {
                i = 0;
                while (i < str.length())
                {
                    if (str[i] == ',')
                        str[i] = ' ';
                    i++;
                }
                stringstream ss(str);
                List<int> *temp = new SupList<int>;
                int num;
                while (ss >> num)
                {
                    temp->push_back(num);
                }
                data->push_back(temp);
            }
            return true;
        }
        return false;
    }
    void printHead(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0)
            return;
        this->nameCol->supPrint(0, nCols);
        if (nRows > this->data->length())
        {
            for (int i = 0; i < this->data->length(); i++)
            {
                cout << endl;
                this->data->get(i)->supPrint(0, nCols);
            }
        }
        else
        {
            for (int i = 0; i < nRows; i++)
            {
                cout << endl;
                this->data->get(i)->supPrint(0, nCols);
            }
        }
    }
    void printTail(int nRows = 5, int nCols = 5) const
    {
        if (nRows <= 0 || nCols <= 0)
            return;
        int a = this->data->length();
        int b = this->nameCol->length();
        if (nCols > b)
            this->nameCol->supPrint(0, nCols);
        else
            this->nameCol->supPrint(b - nCols, b);

        if (nRows > a)
        {
            for (int i = 0; i < this->data->length(); i++)
            {
                if (nCols > b)
                {
                    cout << endl;
                    this->data->get(i)->supPrint(0, nCols);
                }
                else
                {
                    cout << endl;
                    this->data->get(i)->supPrint(b - nCols, b);
                }
            }
        }

        else
        {
            for (int i = a - nRows; i < a; i++)
            {
                if (nCols > b)
                {
                    cout << endl;
                    this->data->get(i)->supPrint(0, nCols);
                }
                else
                {
                    cout << endl;
                    this->data->get(i)->supPrint(b - nCols, b);
                }
            }
        }
    }
    void getShape(int &nRows, int &nCols) const
    {
        nRows = this->data->length();
        nCols = this->data->get(0)->length();
    }
    void columns() const
    {
        this->nameCol->supPrint(0, this->nameCol->length());
    }
    bool drop(int axis = 0, int index = 0, std::string columns = "")
    {
        if (this->data->length() == 0 && axis == 0)
            return false;
        if (axis != 0 && axis != 1)
            return false;
        else if (axis == 0)
        {
            if (index < 0 || index >= this->data->length())
                return false;
            else
            {
                data->get(index)->clear();
                delete data->get(index);
                this->data->remove(index);
                return true;
            }
        }
        else
        {
            for (int i = 0; i < this->nameCol->length(); i++)
            {
                if (columns == this->nameCol->get(i))
                {
                    if (this->nameCol->length() == 1)
                    {
                        for (int j = 0; j < this->data->length(); j++)
                        {
                            data->get(j)->clear();
                            delete data->get(j);
                        }
                        data->clear();
                    }
                    else
                    {
                        for (int j = 0; j < this->data->length(); j++)
                        {
                            this->data->get(j)->remove(i);
                        }
                    }
                    this->nameCol->remove(i);
                    return true;
                }
            }
        }
        return false;
    }
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
    {
        Dataset newsheet;
        int numRows = this->data->length();
        int numCols;
        if (numRows == 0)
            return newsheet;
        else
            numCols = this->data->get(0)->length();
        if (endRow == -1 || endRow >= numRows)
            endRow = numRows - 1;
        if (endCol == -1 || endCol >= numCols)
            endCol = numCols - 1;

        if (startCol >= numCols || startRow >= numRows)
            throw std::out_of_range("get(): Out of range");
        if (startCol <= -1 || startRow <= -1 || startRow > endRow || startCol > endCol || endRow < -1 || endCol < -1)
            throw std::out_of_range("get(): Out of range");

        if (startCol < this->nameCol->length())
            newsheet.nameCol = this->nameCol->subList(startCol, endCol + 1);
        for (int i = startRow; i <= endRow; i++)
        {
            newsheet.data->push_back(this->data->get(i)->subList(startCol, endCol + 1));
        }

        return newsheet;
    }
    double distanceEuclidean(const List<int> *a, const List<int> *b) const
    {
        double distance = 0.0;
        if ( a->length() == 0 && b->length() == 0 ) return 0;

        int arrA[a->length()];
        int arrB[b->length()];
        int i = 0;
        a->getArray(arrA);
        b->getArray(arrB);
        if ( b->length() == 0 ) {
            while ( i < a->length() ){
                distance += pow(arrA[i], 2);
                i++;
            }
        }
        if ( a->length() == 0 ) {
            while ( i < b->length() ){
                distance += pow(arrB[i], 2);
                i++;
            }
        }

        if ( a->length() == b->length() ) {
            while ( i < a->length() ){
                distance += pow(arrA[i] - arrB[i], 2);
                i++;
            }
        }
        else {
            if ( a->length() > b->length() ) {
                while ( b->length() > i  ){
                    distance += pow(arrA[i] - arrB[i], 2);
                    i++;
                }
                while ( i < a->length() ){
                    distance += pow(arrA[i], 2);
                    i++;
                }
            }
            else {
                while ( a->length() > i  ){
                    distance += pow( arrB[i] - arrA[i], 2);
                    i++;
                }
                while ( i < b->length() ){
                    distance += pow(arrB[i], 2);
                    i++;
                }
            }

        }
        return sqrt(distance);
    }
    List<List<int> *> *getData() const
    {
        return this->data;
    }
    Dataset predict(const Dataset &X_train, const Dataset &Y_train, const int k) const
    {
        Dataset result;
        if (X_train.data->length() <= 0 || Y_train.data->length() <= 0 || this->data->length() <= 0 || k <= 0)
            return result;
        if (Y_train.nameCol->length() > 0)
            result.nameCol->push_back(Y_train.nameCol->get(0));

        int length = min(X_train.data->length(), Y_train.data->length());
        double *distance = new double[length];
        int *label = new int[length];

        for (int i = 0; i < this->data->length(); i++)
        {
            int count = 0;
            length = min(X_train.data->length(), Y_train.data->length());
            for (int i = 0; i < length; i++)
            {
                label[i] = Y_train.data->get(i)->get(0); // truyền label Y_train vào mảng label
            }
            for (int j = 0; j < length; j++)
            {
                distance[j] = distanceEuclidean(this->data->get(i), X_train.data->get(j)); // tính distance của dòng i với từng dòng trong X_train
            }
            for (int j = 0; j < length; j++)
            {
                for (int h = length - 1; h >= j + 1; h--)
                {
                    if (distance[h] < distance[h - 1])
                    {
                        int save1;
                        double save2;
                        save2 = distance[h];
                        distance[h] = distance[h - 1];
                        distance[h - 1] = save2;
                        save1 = label[h];
                        label[h] = label[h - 1];
                        label[h - 1] = save1;
                    }
                }
            }
            if (k > length) throw std::out_of_range("get(): Out of range");
            int arr[10] = {0};
            for (int h = 0; h < k; h++)
            {
                arr[label[h]] = arr[label[h]] + 1;
            }
            for (int h = 0; h < 10; h++)
            {
                if (arr[count] < arr[h])
                    count = h;
            }
            List<int> *value = new SupList<int>;
            value->insert(0, count);
            result.data->push_back(value);
        }

        delete[] distance;
        delete[] label;
        return result;
    }
    double score(const Dataset &y_predict) const
    {
        if (y_predict.data->length() == 0 || this->data->length() == 0)
            return -1;
        if (y_predict.data->length() != this->data->length())
            return -1;
        double result = 0;
        int length = min(this->data->length(), y_predict.data->length());
        for (int i = 0; i < length; i++)
        {
            if (this->data->get(i)->get(0) == y_predict.data->get(i)->get(0))
                result++;
        }
        result = result / length;
        return result;
    }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test);

// Please add more or modify as needed