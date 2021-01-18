use super::Sorter;

pub struct InsertSort {
    pub smart: bool,
}

impl Sorter for InsertSort {
    fn sort<T>(&self, slice: &mut [T])
    where
        T: Ord,
    {
        // let smarter = false;
        for unsorted in 1..slice.len() {
            if !self.smart {
                let mut i = unsorted;
                while i > 0 && slice[i - 1] > slice[i] {
                    slice.swap(i - 1, i);
                    i -= 1;
                }
            } else {
                // let i = match slice[0..unsorted].binary_search(&slice[unsorted]) {
                //     Ok(i) => i,
                //     Err(i) => i,
                // };

                let i = slice[0..unsorted]
                    .binary_search(&slice[unsorted])
                    .unwrap_or_else(|i| i);

                slice[i..=unsorted].rotate_right(1);
            }
        }
    }
}

#[test]
fn insertsort_smart_works() {
    let mut things = vec![4, 2, 3, 1];
    InsertSort { smart: true }.sort(&mut things);
    assert_eq!(things, vec![1, 2, 3, 4]);
}

#[test]
fn insertsort_nosmart_works() {
    let mut things = vec![4, 2, 3, 1];
    InsertSort { smart: false }.sort(&mut things);
    assert_eq!(things, vec![1, 2, 3, 4]);
}
