/*
 Thanks to
 https://gist.github.com/busypeoples/b76fd7717d5c4675a55e42a66cead025
 */

exception Empty_list;

module type LinkedList = {
  type t;
  type linkedList('t) =
    | Empty
    | LL('t, linkedList('t));
  let empty: linkedList('t);
  let head: linkedList('t) => 't;
  let tail: linkedList('t) => linkedList('t);
  let insert: ('t, linkedList('t)) => linkedList('t);
  let remove: ('t, linkedList('t)) => linkedList('t);
  let contains: ('t, linkedList('t)) => bool;
  let iter: ('t => unit, linkedList('t)) => unit;
  let map: ('a => 'b, linkedList('a)) => linkedList('b);
  let fold: ('a => 'b, 'b, linkedList('a)) => 'b;
  let toArray: linkedList('t) => list('t);
  let isEmpty: linkedList('t) => bool;
  let size: linkedList('t) => int;
};

type t;

type linkedList('t) =
  | Empty
  | LL('t, linkedList('t));

let empty = Empty;

let head = list =>
  switch (list) {
  | Empty => raise(Empty_list)
  | LL(head, _tail) => head
  };

let tail = list =>
  switch (list) {
  | Empty => Empty
  | LL(_head, tail) => tail
  };

/* Insert value at end of list */
let rec insert = (value, list) =>
  switch (list) {
  | Empty => LL(value, Empty)
  | LL(head, tail) => LL(head, insert(value, tail))
  };

let rec remove = (value, list) =>
  switch (list) {
  | Empty => Empty
  | LL(_head, Empty) => Empty
  | LL(head, LL(nextHead, nextTail) as tail) =>
    if (head === value) {
      LL(nextHead, nextTail);
    } else {
      LL(head, remove(value, tail));
    }
  };

let rec removeBy = (pfn: 't => bool, list) =>
  switch (list) {
  | Empty => Empty
  | LL(_head, Empty) => Empty
  | LL(head, LL(nextHead, nextTail) as tail) =>
    if (pfn(head)) {
      LL(nextHead, nextTail);
    } else {
      LL(head, removeBy(pfn, tail));
    }
  };

let rec contains = (value, list) =>
  switch (list) {
  | Empty => false
  | LL(head, tail) =>
    if (head === value) {
      true;
    } else {
      contains(value, tail);
    }
  };

let rec iter = (fn, list) =>
  switch (list) {
  | Empty => ()
  | LL(head, Empty) => fn(head)
  | LL(head, tail) =>
    fn(head) |> ignore;
    iter(fn, tail);
  };

let rec map = (fn, list) =>
  switch (list) {
  | Empty => Empty
  | LL(head, tail) => LL(fn(head), map(fn, tail))
  };

let rec fold = (fn, acc, list) =>
  switch (list) {
  | Empty => acc
  | LL(head, tail) => fold(fn, fn(acc, head), tail)
  };

let toArray = list => fold((acc, a) => Array.concat([acc, [|a|]]), [||], list);

let isEmpty = list =>
  switch (list) {
  | Empty => true
  | _ => false
  };

let size = list =>
  switch (list) {
  | Empty => 0
  | _ =>
    let count = ref(0);
    iter(_ => count := count^ + 1, list);
    count^;
  };