#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class Node
{
public:
    Node() {}
    Node(T d)
    {
        data = d;
    }
    Node(T d, Node<T> *p, Node<T> *n)
    {
        data = d;
        prev = p;
        next = n;
    }
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template <class T>
class LinkedList
{
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        returnSign = 1;
    }
    void init()
    {
        head = NULL;
        tail = NULL;
        sign = 0;
    }
    void addToTail(T _data)
    {
        Node<T> *new_node = new Node<T>(_data, NULL, NULL);
        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
    }
    void addToHead(T _data)
    {
        Node<T> *new_node = new Node<T>(_data, NULL, NULL);
        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }
    void deleteData(T _data)
    {
        Node<T> *cur = head;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
            return;
        }
        while (cur->next != NULL && cur->data != _data)
            cur = cur->next;
        if (tail->data != _data && cur == tail)
        {
            return;
        }
        else if (cur == head)
        {
            head = cur->next;
            head->prev = NULL;
        }
        else if (cur == tail)
        {
            tail = cur->prev;
            cur->prev->next = NULL;
        }
        else
        {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
    }
    void deleteData(T _data, int n)
    {
        if (n == 0)
            return;
        deleteData(_data);
        deleteData(_data, n - 1);
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList *n)
    {
        Node<T> *cur = n->head;
        out << "(";
        while (cur->next != NULL)
        {
            out << cur->data << ", ";
            cur = cur->next;
        }
        out << cur->data << ")\n";
    }
    Node<T> *head;
    Node<T> *tail;
    bool sign;
    bool returnSign;
};

class BigDecimal
{
public:
    BigDecimal()
    {
        integer->sign = 0;
    }
    BigDecimal(string d)
    {
        integer->init();
        decimal->init();
        int idx;
        for (idx = 0; idx < d.length(); idx++)
        {
            if (d[idx] == '-')
                integer->sign = 1;
            else if (d[idx] >= '0' && d[idx] <= '9')
            {
                string n = "";
                n += d[idx];
                integer->addToTail(n);
            }
            else
                break;
        }
        if (idx < d.length() && d[idx] == '.')
        {
            idx++;
            for (int i = idx; i < d.length(); i++)
            {
                string n = "";
                n += d[i];
                decimal->addToTail(n);
            }
        }
    }
    void deleteZero()
    {
        Node<string> *cur = integer->head;
        while (cur != NULL)
        {
            if (cur->data == "0")
                integer->deleteData("0");
            else
                return;
            cur = cur->next;
        }
    }
    void combine()
    {
        Node<string> *cur = decimal->head;
        while (cur != NULL)
        {
            integer->addToTail(cur->data);
            decimal->deleteData(cur->data);
            cur = cur->next;
        }
    }
    void combine_decimal(int n)
    {
        Node<string> *cur = integer->tail; // n=4
        if (sizeI() - n <= 0)
        {
            for (int i = 0; i < n; i++)
                integer->addToHead("0");
        }
        cur = integer->head;
        n = sizeI() - n;
        while (n--)
        {
            cur = cur->next;
        }
        decimal->deleteData("0");
        while (cur != NULL)
        {
            decimal->addToTail(cur->data);
            cur->data = "!";
            cur = cur->next;
            integer->deleteData("!");
        }
    }
    int sizeI()
    {
        int n = 0;
        Node<string> *cur = integer->head;
        while (cur != NULL)
        {
            n++;
            cur = cur->next;
        }
        return n;
    }
    int sizeD()
    {
        int n = 0;
        Node<string> *cur = decimal->head;
        while (cur != NULL)
        {
            n++;
            cur = cur->next;
        }
        return n;
    }
    BigDecimal *bankerRound()
    {
        BigDecimal *b1 = new BigDecimal;
        BigDecimal *tmp = new BigDecimal;
        Node<string> *cur = decimal->head;
        if (cur == NULL)
            return this;
        for (int i = 0; i < 2; i++)
        {
            cur = cur->next;
            if (cur == NULL)
                return this;
        }
        if (cur->next != NULL && cur->next->data != "0")
        {
            int num = stoi(cur->data);
            num++;
            cur->data = to_string(num);
        }
        b1->integer->addToHead("0");
        b1->decimal->addToTail("0");
        b1->decimal->addToTail("1");
        int n = stoi(cur->data);
        if (n <= 4)
        {
            while (cur != NULL)
            {
                cur->data = "!";
                decimal->deleteData("!");
                cur = cur->next;
            }
            return this;
        }
        else if (n >= 6)
        {
            while (cur != NULL)
            {
                cur->data = "!";
                decimal->deleteData("!");
                cur = cur->next;
            }
            if (this->integer->sign)
                return *this - b1;
            return *this + b1;
        }
        else if (n == 5)
        {
            int m = stoi(cur->prev->data);
            if (m % 2 == 0)
            { // even
                while (cur != NULL)
                {
                    cur->data = "!";
                    decimal->deleteData("!");
                    cur = cur->next;
                }
                return this;
            }
            else
            { // odd
                while (cur != NULL)
                {
                    cur->data = "!";
                    decimal->deleteData("!");
                    cur = cur->next;
                }
                if (this->integer->sign)
                    return *this - b1;
                return *this + b1;
            }
        }
    }
    void match(BigDecimal *b)
    {
        if (sizeI() > b->sizeI())
        {
            int s = sizeI() - b->sizeI();
            for (int i = 0; i < s; i++)
                b->integer->addToHead("0");
        }
        if (sizeI() < b->sizeI())
        {
            int s = b->sizeI() - sizeI();
            for (int i = 0; i < s; i++)
                integer->addToHead("0");
        }
        if (sizeD() > b->sizeD())
        {
            int s = sizeD() - b->sizeD();
            for (int i = 0; i < s; i++)
                b->decimal->addToTail("0");
        }
        if (sizeD() < b->sizeD())
        {
            int s = b->sizeD() - sizeD();
            for (int i = 0; i < s; i++)
                decimal->addToTail("0");
        }
    }
    int compare(BigDecimal *b)
    { // this > b => return true
        string myi = "", bi = "";
        Node<string> *cur = integer->head;
        while (cur != NULL)
        {
            myi += cur->data;
            cur = cur->next;
        }
        cur = b->integer->head;
        while (cur != NULL)
        {
            bi += cur->data;
            cur = cur->next;
        }
        if (stod(myi) > stod(bi))
            return 1;
        else if (stod(myi) < stod(bi))
            return 0;
        else if (stod(myi) == stod(bi))
            return -1;
    }
    int quotient(BigDecimal *b)
    {
        int q = -1;
        BigDecimal *tmp = new BigDecimal("0.0");
        while (this->compare(tmp))
        {
            tmp = *tmp + b;
            q++;
        }
        tmp = *tmp - b;
        tmp = *this - tmp;
        // cout<<tmp<<q;
        return q;
    }
    void combine_quo(int n)
    {
        if (n <= 0)
        {
            n = abs(n) + 1;
            Node<string> *cur = integer->head;
            while (n--)
            {
                cur = cur->next;
            }
            while (cur != NULL)
            {
                decimal->addToTail(cur->data);
                cur->data = "!";
                cur = cur->next;
                integer->deleteData("!");
            }
        }
        else if (n > 0)
        {
            while (n--)
            {
                integer->addToHead("0");
            }
            Node<string> *cur = integer->head->next;
            while (cur != NULL)
            {
                decimal->addToTail(cur->data);
                cur->data = "!";
                cur = cur->next;
                integer->deleteData("!");
            }
        }
    }
    BigDecimal *operator+(BigDecimal *bigDecimal)
    {
        bool isNeg = 0;
        if (!(integer->sign) && bigDecimal->integer->sign)
        {
            bigDecimal->integer->sign = 0;
            return *this - bigDecimal;
        }
        else if (integer->sign && !bigDecimal->integer->sign)
        {
            integer->sign = 0;
            return *bigDecimal - this;
        }
        else if (integer->sign && bigDecimal->integer->sign)
            isNeg = 1;
        this->match(bigDecimal);
        BigDecimal *b = new BigDecimal;
        int carry = 0;
        int n;
        Node<string> *cur = decimal->tail, *curB = bigDecimal->decimal->tail;
        while (cur != NULL)
        {
            n = stoi(cur->data) + stoi(curB->data) + carry;
            carry = 0;
            if (n >= 10)
            {
                n -= 10;
                carry = 1;
            }
            b->decimal->addToHead(to_string(n));
            cur = cur->prev;
            curB = curB->prev;
        }
        cur = integer->tail, curB = bigDecimal->integer->tail;
        while (cur != NULL)
        {
            n = stoi(cur->data) + stoi(curB->data) + carry;
            carry = 0;
            if (n >= 10)
            {
                n -= 10;
                carry = 1;
            }
            b->integer->addToHead(to_string(n));
            cur = cur->prev;
            curB = curB->prev;
        }
        if (carry)
            b->integer->addToHead("1");
        if (isNeg)
            b->integer->sign = 1;
        // b=b->bankerRound();
        return b;
    }
    BigDecimal *operator-(BigDecimal *bigDecimal)
    {
        if ((!integer->sign) && bigDecimal->integer->sign)
        { //(+a)-(-b) => a+b
            bigDecimal->integer->sign = 0;
            return *this + bigDecimal;
        }
        else if (integer->sign && (!bigDecimal->integer->sign))
        { //(-a)-(+b) => (-a)+(-b)
            bigDecimal->integer->sign = 1;
            return *this + bigDecimal;
        }
        else if (integer->sign && bigDecimal->integer->sign)
        { //(-a)-(-b) => (-a)+b
            bigDecimal->integer->sign = 0;
            return *this + bigDecimal;
        }
        this->match(bigDecimal);
        BigDecimal *b = new BigDecimal();
        Node<string> *cur = integer->head, *curB = bigDecimal->integer->head;
        int flag = 1;
        while (cur != NULL)
        {
            if (cur->data < curB->data)
            {
                BigDecimal *b1 = *bigDecimal - this;
                b1->integer->sign = 1;
                return b1;
            }
            else if (cur->data > curB->data)
                break;
            else if (cur->data == curB->data)
            {
                cur = cur->next;
                curB = curB->next;
            }
            if (cur == NULL && flag)
            {
                cur = decimal->head;
                curB = bigDecimal->decimal->head;
                flag = 0;
            }
        }
        int n = 0, barrow = 0;
        cur = decimal->tail, curB = bigDecimal->decimal->tail;
        while (cur != NULL)
        {
            n = stoi(cur->data) - stoi(curB->data) - barrow;
            barrow = 0;
            if (n < 0)
            {
                n += 10;
                barrow = 1;
            }
            b->decimal->addToHead(to_string(n));
            cur = cur->prev;
            curB = curB->prev;
        }
        cur = integer->tail, curB = bigDecimal->integer->tail;
        while (cur != NULL)
        {
            n = stoi(cur->data) - stoi(curB->data) - barrow;
            barrow = 0;
            if (n < 0)
            {
                n += 10;
                barrow = 1;
            }
            b->integer->addToHead(to_string(n));
            cur = cur->prev;
            curB = curB->prev;
        }
        // b=b->bankerRound();
        return b;
    }
    BigDecimal *operator*(BigDecimal *bigDecimal)
    {
        BigDecimal *tmp = new BigDecimal("0.0");
        if (sizeI() + sizeD() < bigDecimal->sizeI() + bigDecimal->sizeD())
            return *bigDecimal * this;
        int isNeg = 0;
        if (!(integer->sign) && bigDecimal->integer->sign)
        {
            bigDecimal->integer->sign = 0;
            isNeg = 1;
        }
        else if (integer->sign && !(bigDecimal->integer->sign))
        {
            integer->sign = 0;
            isNeg = 1;
        }
        else if (integer->sign && bigDecimal->integer->sign)
        {
            integer->sign = 0;
            bigDecimal->integer->sign = 0;
        }
        int flag = 0, cnt = sizeD() + bigDecimal->sizeD();
        this->combine();
        bigDecimal->combine();
        if (this->compare(tmp) == -1 || bigDecimal->compare(tmp) == -1)
            return tmp;
        Node<string> *curB = bigDecimal->integer->tail;
        while (curB != NULL)
        {
            int n = stoi(curB->data);
            if (flag)
                integer->addToTail("0");
            for (int i = 0; i < n; i++)
            {
                tmp = *tmp + this;
            }
            flag = 1;
            curB = curB->prev;
        }
        tmp->deleteZero();
        tmp->combine_decimal(cnt);
        if (isNeg)
            tmp->integer->sign = 1;
        return tmp;
    }
    BigDecimal *operator/(BigDecimal *bigDecimal)
    {
        int isNeg = 0;
        if (!(integer->sign) && bigDecimal->integer->sign)
        {
            bigDecimal->integer->sign = 0;
            isNeg = 1;
        }
        else if (integer->sign && !(bigDecimal->integer->sign))
        {
            integer->sign = 0;
            isNeg = 1;
        }
        else if (integer->sign && bigDecimal->integer->sign)
        {
            integer->sign = 0;
            bigDecimal->integer->sign = 0;
        }
        Node<string> *cur = decimal->head;
        int move = bigDecimal->sizeD(), flag = 1, cnt = 0;
        bigDecimal->combine();
        for (int i = 0; i < move; i++)
        {
            if (cur == NULL && flag)
            {
                cur = integer->tail;
                flag = 0;
            }
            else if (flag)
            {
                string s = cur->data;
                integer->addToTail(s);
                decimal->deleteData(s);
                cur = cur->next;
            }
            if (!flag)
            {
                integer->addToTail("0");
            }
        }
        if (sizeD() != 0)
        {
            int n = sizeD();
            while (n--)
                bigDecimal->integer->addToTail("0");
            this->combine();
        }
        this->deleteZero();
        bigDecimal->deleteZero();
        if (sizeI() != bigDecimal->sizeI())
        {
            cnt = bigDecimal->sizeI() - sizeI(); // + => move left  - => move right
            if (sizeI() > bigDecimal->sizeI())
            {
                for (int i = 0; i < abs(cnt); i++)
                    bigDecimal->integer->addToTail("0");
            }
            else if (sizeI() < bigDecimal->sizeI())
            {
                for (int i = 0; i < cnt; i++)
                    integer->addToTail("0");
            }
        }
        BigDecimal *tmp = new BigDecimal("0.0");
        BigDecimal *z = new BigDecimal("0.0");
        BigDecimal *ans = new BigDecimal;
        if (cnt >= 3)
            return tmp;
        int qt, inflag = 1;
        tmp = this;
        int c = abs(cnt) + 3;
        while (c--)
        {
            int deflag = 0;
            if (tmp->compare(z) == -1)
            {
                for (int i = 0; i < c; i++)
                    ans->integer->addToTail("0");
                break;
            }
            while (!tmp->compare(bigDecimal))
            {
                if (inflag || deflag)
                    ans->integer->addToTail("0");
                tmp->integer->addToTail("0");
                deflag = 1;
            }
            if (tmp->compare(bigDecimal) == 1 || tmp->compare(bigDecimal) == -1)
            {
                qt = tmp->quotient(bigDecimal);
                ans->integer->addToTail(to_string(qt));
                inflag = 0;
                for (int i = 0; i < qt; i++)
                    tmp = *tmp - bigDecimal;
            }
        }
        if (cnt < 0)
        {
            ans->combine_quo(cnt);
        }
        else if (cnt == 0)
        {
            ans->combine_quo(0);
        }
        else if (cnt > 0)
        {
            ans->combine_quo(cnt);
        }
        if (isNeg)
            ans->integer->sign = 1;
        return ans;
    }
    BigDecimal *operator^(BigDecimal *bigDecimal)
    {
        Node<string> *cur = integer->head, *curB = bigDecimal->integer->head;
        string mys = "", bs = "";
        while (cur != NULL)
        {
            mys += cur->data;
            cur = cur->next;
        }
        mys += '.';
        cur = decimal->head;
        while (cur != NULL)
        {
            mys += cur->data;
            cur = cur->next;
        }
        if (bigDecimal->integer->sign)
            bs += '-';
        while (curB != NULL)
        {
            bs += curB->data;
            curB = curB->next;
        }
        curB = bigDecimal->decimal->head;
        bs += '.';
        while (curB != NULL)
        {
            bs += curB->data;
            curB = curB->next;
        }
        if (bs[bs.length() - 1] == '.' && !(bigDecimal->integer->sign))
        { // b is integer
            bs += '0';
            int isNeg = 0;
            BigDecimal *tmp = new BigDecimal("1.0");
            BigDecimal *tmp2 = new BigDecimal("1.0");
            if (integer->sign)
            {
                if (stoi(bs) % 2 == 1)
                {
                    this->integer->sign = 0;
                    isNeg = 1;
                }
                else
                {
                    tmp->integer->sign = 0;
                    this->integer->sign = 0;
                }
            }
            if (stoi(bs) > 300)
            {
                for (int i = 0; i < 300; i++)
                    tmp = *tmp * this;
                for (int i = 0; i < stoi(bs) - 300; i++)
                    tmp2 = *tmp2 * this;
                tmp = *tmp * tmp2;
            }
            else
                for (int i = 0; i < stoi(bs); i++)
                {
                    tmp = *tmp * this;
                }
            if (isNeg)
                tmp->integer->sign = 1;
            return tmp;
        }
        else
        {
            BigDecimal *ans = new BigDecimal;
            int b = (int)stod(bs);
            int flag = 1;
            // if (integer->sign && b%2==1) {
            //     integer->sign=0;
            //     ans->integer->sign=1;
            // }
            double n = pow(stod(mys), stod(bs));
            string s = to_string(n);
            for (int i = 0; i < s.length(); i++)
            {
                if ((s[i] >= '0' && s[i] <= '9') && flag)
                {
                    string ss = "";
                    ss += s[i];
                    ans->integer->addToTail(ss);
                }
                if (s[i] == '.')
                {
                    flag = 0;
                }
                if ((s[i] >= '0' && s[i] <= '9') && !flag)
                {
                    string ss = "";
                    ss += s[i];
                    ans->decimal->addToTail(ss);
                }
            }
            // cout<<ans;
            return ans;
        }
    }
    friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal)
    {
        Node<string> *cur = bigDecimal->integer->head;
        if (bigDecimal->integer->sign)
            out << "-";
        while (cur->data == "0" && cur->next != NULL)
            cur = cur->next;
        while (cur != NULL)
        {
            cout << cur->data;
            cur = cur->next;
        }
        int cnt = 0;
        out << ".";
        if (bigDecimal->decimal->head != NULL)
        {
            cur = bigDecimal->decimal->head;
            while (cur != NULL)
            {
                out << cur->data;
                cur = cur->next;
                cnt++;
            }
        }
        while (cnt < 2)
        {
            out << "0";
            cnt++;
        }
        out << endl;
        return out;
    }
    friend std::istream &operator>>(std::istream &in, BigDecimal *data)
    {
        data->integer->init();
        data->decimal->init();
        string d;
        in >> d;
        int idx;
        for (idx = 0; idx < d.length(); idx++)
        {
            if (d[idx] == '-')
                data->integer->sign = 1;
            else if (d[idx] >= '0' && d[idx] <= '9')
            {
                string n = "";
                n += d[idx];
                data->integer->addToTail(n);
            }
            else
                break;
        }
        if (idx < d.length() && d[idx] == '.')
        {
            idx++;
            for (int i = idx; i < d.length(); i++)
            {
                string n = "";
                n += d[i];
                data->decimal->addToTail(n);
            }
        }
        // else
        //     data->decimal->addToTail("0");
        return in;
    }

private:
    LinkedList<string> *integer = new LinkedList<string>;
    LinkedList<string> *decimal = new LinkedList<string>;
};
int main()
{
    BigDecimal *bigDecimal1 = new BigDecimal();
    BigDecimal *bigDecimal2 = new BigDecimal();
    BigDecimal *ans;
    char operation;
    while (cin >> bigDecimal1 >> operation >> bigDecimal2)
    {
        switch (operation)
        {
        case '+':
            ans = *bigDecimal1 + bigDecimal2;
            cout << ans->bankerRound();
            break;
        case '-':
            ans = *bigDecimal1 - bigDecimal2;
            cout << ans->bankerRound();
            break;
        case '*':
            ans = *bigDecimal1 * bigDecimal2;
            cout << ans->bankerRound();
            break;
        case '/':
            ans = *bigDecimal1 / bigDecimal2;
            cout << ans->bankerRound();
            break;
        case '^':
            ans = *bigDecimal1 ^ bigDecimal2;
            cout << ans->bankerRound();
            break;
        default:
            break;
        }
    }
    return 0;
}