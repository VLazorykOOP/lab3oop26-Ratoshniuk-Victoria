#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
    double a, b, c;
    int color;

public:

    Triangle() : a(1), b(1), c(1), color(0) {}
    Triangle(double a, double b, double c, int color = 0) {
        setSides(a, b, c);
        setColor(color);
    }

    void setSides(double a, double b, double c) {
        if (a > 0 && b > 0 && c > 0 &&
            a + b > c && a + c > b && b + c > a) {
            this->a = a;
            this->b = b;
            this->c = c;
        }
        else {
            cout << "Error: incorrect triangle\n";
        }
    }

    void setColor(int c) {
        if (c >= 0) color = c;
        else cout << "Error: wrong color\n";
    }

    double getA() { return a; }
    double getB() { return b; }
    double getC() { return c; }
    int getColor() { return color; }

    double perimeter() {
        return a + b + c;
    }

    double area() {
        double p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    void print() {
        cout << "\nTriangle: ";
        cout << "a=" << a << " b=" << b << " c=" << c;
        cout << " color=" << color;
        cout << " P=" << perimeter();
        cout << " S=" << area() << endl;
    }
};

class VectorLong {
    long* arr;
    int size;
    int state;
    static int count;

public:

    VectorLong() {
        size = 1;
        arr = new long[size] {0};
        state = 0;
        count++;
    }

    VectorLong(int n) {
        if (n <= 0) {
            size = 0;
            arr = nullptr;
            state = -1;
        }
        else {
            size = n;
            arr = new long[size] {0};
            state = 0;
        }
        count++;
    }

    VectorLong(int n, long value) {
        if (n <= 0) {
            size = 0;
            arr = nullptr;
            state = -1;
        }
        else {
            size = n;
            arr = new long[size];
            for (int i = 0; i < size; i++)
                arr[i] = value;
            state = 0;
        }
        count++;
    }

    VectorLong(const VectorLong& v) {
        size = v.size;
        arr = new long[size];
        for (int i = 0; i < size; i++)
            arr[i] = v.arr[i];
        state = v.state;
        count++;
    }

    VectorLong& operator=(const VectorLong& v) {
        if (this != &v) {
            delete[] arr;
            size = v.size;
            arr = new long[size];
            for (int i = 0; i < size; i++)
                arr[i] = v.arr[i];
            state = v.state;
        }
        return *this;
    }
    ~VectorLong() {
        delete[] arr;
        count--;
    }

    void set(int i, long val = 0) {
        if (i >= 0 && i < size)
            arr[i] = val;
        else
            state = -2;
    }

    long get(int i) {
        if (i >= 0 && i < size)
            return arr[i];
        state = -2;
        return 0;
    }

    VectorLong add(VectorLong& v) {
        int n = min(size, v.size);
        VectorLong res(n);
        for (int i = 0; i < n; i++)
            res.arr[i] = arr[i] + v.arr[i];
        return res;
    }

    VectorLong sub(VectorLong& v) {
        int n = min(size, v.size);
        VectorLong res(n);
        for (int i = 0; i < n; i++)
            res.arr[i] = arr[i] - v.arr[i];
        return res;
    }

    VectorLong mul(unsigned int k) {
        VectorLong res(size);
        for (int i = 0; i < size; i++)
            res.arr[i] = arr[i] * k;
        return res;
    }

    bool isLess(VectorLong& v) {
        for (int i = 0; i < min(size, v.size); i++)
            if (arr[i] >= v.arr[i]) return false;
        return true;
    }

    void print() {
        cout << "Vector: ";
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    static int getCount() {
        return count;
    }
};

int VectorLong::count = 0;

int main() {
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1 - Triangle\n";
        cout << "2 - Vector\n";
        cout << "0 - Exit\n";
        cin >> choice;
        switch (choice) {

        case 1: {
            double a, b, c;
            int color;
            cout << "Enter sides a b c: ";
            cin >> a >> b >> c;
            cout << "Enter color: ";
            cin >> color;

            Triangle t(a, b, c, color);
            t.print();
            break;
        }

        case 2: {
            int n;
            cout << "Enter size: ";
            cin >> n;

            VectorLong v1(n), v2(n);

            cout << "Enter elements of vector 1:\n";
            for (int i = 0; i < n; i++) {
                long x;
                cin >> x;
                v1.set(i, x);
            }

            cout << "Enter elements of vector 2:\n";
            for (int i = 0; i < n; i++) {
                long x;
                cin >> x;
                v2.set(i, x);
            }

            VectorLong sum = v1.add(v2);
            VectorLong diff = v1.sub(v2);
            VectorLong mul = v1.mul(2);

            cout << "Sum: "; sum.print();
            cout << "Diff: "; diff.print();
            cout << "Mul *2: "; mul.print();

            break;
        }

        }

    } while (choice != 0);

    return 0;
}