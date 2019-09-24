open Tree;

Js.log("----------------------------------------");

let t2 = Tree("a", [Tree("b", [Leaf("c"), Leaf("d")]), Tree("e", [Leaf("f"), Leaf("g")])]);

Js.log(t2);

/* walk(t2); */