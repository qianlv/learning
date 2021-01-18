use super::Sorter;

pub struct SelectionSort;

impl Sorter for SelectionSort {
    fn sort<T>(&self, slice: &mut [T])
    where
        T: Ord,
    {
        for unsorted in 0..slice.len() {
            let (smallest_in_rest, _) = slice[unsorted..]
                .iter()
                .enumerate()
                .min_by_key(|&(_, v)| v)
                .expect("slice is non-empty");

            let smallest_in_rest = unsorted + smallest_in_rest;
            slice.swap(unsorted, smallest_in_rest);
        }
    }
}

#[test]
fn it_works() {
    let mut things = vec![4, 2, 3, 1];
    SelectionSort.sort(&mut things);
    assert_eq!(things, vec![1, 2, 3, 4]);
}
