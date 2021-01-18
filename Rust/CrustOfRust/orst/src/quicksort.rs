use super::Sorter;

pub struct QuickSort;

fn quicksort<T: Ord>(slice: &mut [T]) {
    match slice.len() {
        0 | 1 => return,
        2 => {
            if slice[0] > slice[1] {
                slice.swap(0, 1);
            }
            return;
        }
        _ => {}
    }

    let (pivot, rest) = slice.split_first_mut().expect("slice is non-empty");

    let mut left = 0;
    for i in 0..rest.len() {
        if rest[i] <= *pivot {
            rest.swap(left, i);
            left += 1;
        }
    }

    // while left <= right {
    //     if rest[left] <= *pivot {
    //         left += 1;
    //     } else {
    //         rest.swap(left, right);
    //         right -= 1;
    //     }
    // }

    left += 1;

    slice.swap(0, left - 1);

    // let (left, right) = slice.split_at_mut(left - 1);
    quicksort(&mut slice[0..(left - 1)]);
    quicksort(&mut slice[left..]);
}

impl Sorter for QuickSort {
    fn sort<T>(&self, slice: &mut [T])
    where
        T: Ord,
    {
        quicksort(slice);
    }
}

#[test]
fn it_works() {
    let mut things = vec![4, 2, 3, 1];
    QuickSort.sort(&mut things);
    assert_eq!(things, vec![1, 2, 3, 4]);
}
