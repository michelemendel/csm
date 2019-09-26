let fmtLevel1 = (level, d, str) => {
  let spc = Js.Array.joinWith("", Array.make(level * d, " "));
  spc ++ str;
};

let fmtLevel = (level, d, str) => {
  let fmt = Scanf.format_from_string("%" ++ string_of_int(level * d) ++ "s%s", "%s%s");
  Printf.sprintf(fmt, "", str);
};

let string_of_array = (sep, arr): string => Js.Array.joinWith(sep, arr);