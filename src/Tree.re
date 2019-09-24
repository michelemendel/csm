type t =
  | Leaf(string)
  | Tree(string, list(t));

/* let rec walk = (fn, tree) =>
   switch (tree) {
   | Leaf(id) => [fn(id)]
   | Tree(id, children) => {
       List.map(walk(fn), children)}
   }; */