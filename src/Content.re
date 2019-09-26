type contentKV = {
  ntype: string,
  label: string,
};

module type Content = {
  type t;
  type content('t) =
    | Content('t);
  let make: contentKV => content(contentKV);
};

type t =
  | Content(contentKV);

let empty = Content({ntype: "", label: ""});

let make = contentKV => Content(contentKV);