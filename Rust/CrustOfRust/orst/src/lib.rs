pub trait Sorter {
    fn sort<T>(&self, slice: &mut [T])
    where
        T: Ord;
}

// fn sort<T, S>(slice: &mut [T])
// where
//     T: Ord,
//     S: Sorter,
// {
//     S:sort(slice);
// }

mod bubblesort;
mod insertsort;
mod quicksort;
mod selectionsort;

pub use bubblesort::BubbleSort;
pub use insertsort::InsertSort;
pub use quicksort::QuickSort;
pub use selectionsort::SelectionSort;

#[cfg(test)]
mod tests {
    use super::*;

    struct StdSorter;
    impl Sorter for StdSorter {
        fn sort<T>(&self, slice: &mut [T])
        where
            T: Ord,
        {
            slice.sort();
        }
    }
    #[test]
    fn std_works() {
        let mut things = vec![4, 2, 3, 1];
        StdSorter.sort(&mut things);
        assert_eq!(things, vec![1, 2, 3, 4]);
    }
}