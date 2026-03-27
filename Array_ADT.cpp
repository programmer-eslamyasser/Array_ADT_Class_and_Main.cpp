#include <iostream>
using namespace std;

class Array
{
private:
    int _size;    // الحجم الكلي للأراي (أقصى عدد عناصر ممكن)
    int _length;  // عدد العناصر الموجودة فعليًا
    int* _items;  // مؤشر على أول عنصر في الأراي

public:
    // Constructor: بيحدد حجم الأراي ويحجز مكان في الذاكرة
    Array(int arrSize)
    {
        _size = arrSize;
        _length = 0;
        _items = new int[arrSize];
    }

    // Destructor: بيفرغ الذاكرة بعد انتهاء استخدام الأراي
    ~Array()
    {
        delete[] _items;
    }

    // إدخال عناصر من المستخدم
    void Fill()
    {
        int num_of_items;
        cout << "How many items do you want to fill?\n";
        cin >> num_of_items;

        // التأكد إن العدد لا يتعدى الحجم
        if (num_of_items > _size)
        {
            cout << "You cannot exceed the array size\n";
            return;
        }

        // إدخال العناصر وتحديث length
        for (int i = 0; i < num_of_items; i++)
        {
            cout << "Enter item number " << i << ": ";
            cin >> _items[i];
            _length++;
        }
    }

    // عرض العناصر الموجودة
    void Display()
    {
        cout << "Array content: ";
        for (int i = 0; i < _length; i++)
        {
            cout << _items[i] << " ";
        }
        cout << "\n";
    }

    // طباعة معلومات الأراي (الحجم وعدد العناصر)
    void PrintInfo()
    {
        cout << "\n[ Array Info ]\n";
        cout << "Size   = " << _size << "\n";
        cout << "Length = " << _length << "\n";
    }

    // البحث عن عنصر وإرجاع مكانه
    int Search(int key)
    {
        for (int i = 0; i < _length; i++)
        {
            if (_items[i] == key)
                return i;
        }
        return -1; // لو مش موجود
    }

    // إضافة عنصر في نهاية الأراي
    void Append(int newItem)
    {
        // لازم يكون فيه مساحة فاضية
        if (_length < _size)
        {
            _items[_length++] = newItem;
        }
        else
        {
            cout << "Array is full\n";
        }
    }

    // إدخال عنصر في مكان معين
    void Insert(int index, int newItem)
    {
        // لازم index يكون صحيح وكمان فيه مساحة
        if (index >= 0 && index <= _length && _length < _size)
        {
            // نحرك العناصر لليمين
            for (int i = _length; i > index; i--)
            {
                _items[i] = _items[i - 1];
            }

            _items[index] = newItem;
            _length++;
        }
        else
        {
            cout << "Invalid index or array is full\n";
        }
    }

    // حذف عنصر من مكان معين
    void Delete(int index)
    {
        // التأكد إن المكان صحيح
        if (index >= 0 && index < _length)
        {
            // نحرك العناصر لليسار
            for (int i = index; i < _length - 1; i++)
            {
                _items[i] = _items[i + 1];
            }

            _length--;
        }
        else
        {
            cout << "Invalid index\n";
        }
    }

    // تكبير حجم الأراي
    void Enlarge(int newSize)
    {
        // لازم الحجم الجديد يكون أكبر
        if (newSize <= _size)
        {
            cout << "New size must be greater than current size\n";
            return;
        }

        // إنشاء أراي جديدة أكبر
        int* newArray = new int[newSize];

        // نقل العناصر القديمة
        for (int i = 0; i < _length; i++)
        {
            newArray[i] = _items[i];
        }

        // حذف الأراي القديمة من الذاكرة
        delete[] _items;

        // جعل المؤشر يشير للأراي الجديدة
        _items = newArray;
        _size = newSize;

        cout << "Array enlarged successfully\n";
    }

    // دمج أراي أخرى مع الحالية
    void Merge(const Array& other)
    {
        // حساب العدد الكلي بعد الدمج
        int total = _length + other._length;

        // لو المساحة مش كفاية نكبر
        if (total > _size)
        {
            Enlarge(total);
        }

        // إضافة عناصر الأراي الثانية
        for (int i = 0; i < other._length; i++)
        {
            _items[_length++] = other._items[i];
        }

        cout << "Merged successfully\n";
    }
};

int main()
{
    cout << "=== Array ADT Demo ===\n";

    int arraySize;
    cout << "Enter array size: ";
    cin >> arraySize;

    Array arr(arraySize);

    // إدخال البيانات
    arr.Fill();
    arr.Display();
    arr.PrintInfo();

    // البحث
    int key;
    cout << "\nEnter value to search: ";
    cin >> key;

    int index = arr.Search(key);
    if (index == -1)
        cout << "Not found\n";
    else
        cout << "Found at index: " << index << "\n";

    // إضافة عنصر
    int newItem;
    cout << "\nEnter item to append: ";
    cin >> newItem;

    arr.Append(newItem);
    arr.Display();
    arr.PrintInfo();

    // إدخال عنصر في مكان معين
    cout << "\nEnter index and item to insert: ";
    cin >> index >> newItem;

    arr.Insert(index, newItem);
    arr.Display();
    arr.PrintInfo();

    // حذف عنصر
    cout << "\nEnter index to delete: ";
    cin >> index;

    arr.Delete(index);
    arr.Display();
    arr.PrintInfo();

    // تكبير الأراي
    cout << "\nEnter new size to enlarge: ";
    int newSize;
    cin >> newSize;

    arr.Enlarge(newSize);
    arr.PrintInfo();

    // دمج أراي أخرى
    cout << "\nEnter second array size: ";
    int size2;
    cin >> size2;

    Array arr2(size2);
    arr2.Fill();

    arr.Merge(arr2);
    arr.Display();
    arr.PrintInfo();

    return 0;
}
