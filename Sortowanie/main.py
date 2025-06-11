# Zadanie 1 -> Merge Sort
def merge_sort(pairs):
    if len(pairs) <= 1:
        return pairs

    mid = len(pairs) // 2
    left = merge_sort(pairs[:mid])
    right = merge_sort(pairs[mid:])

    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if left[i] < right[j]:  # domyślne porównanie krotek (x, y)
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])
    
    return result
 

# Zadanie 2 -> Quick Sort z pojedynczą rekurencją
def quicksort_iterative(arr):
    stack = [(0, len(arr) - 1)]

    while stack:
        low, high = stack.pop()
        if low < high:
            pivot_index = partition(arr, low, high)
            
            # Rekurencja tylko na mniejszej stronie
            if pivot_index - low < high - pivot_index:
                stack.append((pivot_index + 1, high))  # większa część iteracyjnie
                stack.append((low, pivot_index - 1))   # mniejsza do "rekurencji"
            else:
                stack.append((low, pivot_index - 1))
                stack.append((pivot_index + 1, high))
    return arr

def partition(arr, low, high):
    pivot = arr[high]  # Ostatni element -> pivot
    i = low - 1
    for j in range(low, high):
        if arr[j] > pivot:  # Większe na lewo -> sortowanie malejąco
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[high] = arr[high], arr[i + 1]
    return i + 1

# Zadanie 3 -> QuickSort hybryda
def hybrid_quick_sort(arr, low, high):
    while low < high:
        if high - low + 1 < 10:
            insertion_sort(arr, low, high) # Sortowanie przez wstawianie dla malych zakresów
            break
        else:
            pivot_index = partition(arr, low, high)
            
            # Rekurencja na mniejszej, iteracja na większej części --> (oszczędność stosu)
            if pivot_index - low < high - pivot_index:
                hybrid_quick_sort(arr, low, pivot_index - 1)
                low = pivot_index + 1
            else:
                hybrid_quick_sort(arr, pivot_index + 1, high)
                high = pivot_index - 1

# Sortowanie przez wstawianie
def insertion_sort(arr, low, high):
    for i in range(low + 1, high + 1):
        key = arr[i]
        j = i - 1
        while j >= low and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# Zadanie 4
def find_student(student_data):
    student_data = [record.split() for record in student_data]
    student_ranking = {}
    for student in student_data:
        index = student[0]
        points_sum = 0
        for i in range(1, len(student)):
            points_sum += int(student[i]) * 0.5

        student_ranking.update({index: points_sum})
        
    print(student_ranking)

def main():
    # Zad 1
    with open('pary_liczb.txt', 'r', encoding='utf-8') as f:
        pairs = [tuple(map(int, line.split())) for line in f]

    sorted_pairs = merge_sort(pairs)
    print("\n# Zadanie 1:")
    for x, y in sorted_pairs:
        print(x, y)

    # Zad 2
    with open('imiona_nazwiska.txt', 'r', encoding='utf-8') as f:
        people = [tuple(line.strip().split()) for line in f if line.strip()]

    people = quicksort_iterative(people)
    print("\n# Zadanie 2:")
    print(people)

    # Zad 3
    with open('ciagi_znakow.txt', 'r', encoding='utf-8') as f:
        strings = [line.strip() for line in f if line.strip()]

    hybrid_quick_sort(strings, 0, len(strings) - 1)
    print("\n# Zadanie 3:")
    print(strings)

    # Zad 4
    with open('students_data_fixed.txt', 'r', encoding='utf-8') as f:
        students_data = [line.strip() for line in f if line.strip()]

    print("\n# Zadanie 4:")
    find_student(students_data)
    
if __name__ == "__main__":
    main()