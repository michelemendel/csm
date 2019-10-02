/*
 Keep nodes in the lookup table for fast access
 */

module LT = Map.Make(String);

let makeLT = () => LT.empty;

let addLT = LT.add;

let getLT = (uuid, lt) =>
  switch (LT.find(uuid, lt)) {
  | exception Not_found => None
  | node => Some(node)
  };

let removeLT = LT.remove;

let existsLT = LT.mem;

let lenLT = LT.cardinal;