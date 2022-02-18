open Printf;;

let printf_list format lst = printf "[";
  let rec _printf_lst_rec fmt ls = match ls with
    | [] -> printf "]\n"
    | [el] -> printf fmt el; printf "]\n"
    | h :: t -> printf fmt h; printf ";"; _printf_lst_rec fmt t
  in _printf_lst_rec format lst;;


let reverse_digits n = 
  if n >= 0 && n <= 9 then n
  else
    let rec build_rev acc x =
      if x = 0 then acc
      else  build_rev (acc*10 + x mod 10) (x/10)
    in build_rev 0 n;;  


let rec reversed_digits_list n =
  if n >= 0 && n <= 9 then [n]
  else (n mod 10) :: reversed_digits_list (n/10);;

let digits_list n = reversed_digits_list (reverse_digits n);;

let filtered_digits_list cond n = List.filter cond (digits_list n);;


let rec num_from_reversed_digits_list ls = match ls with
  | [] -> 0
  | [n] -> n
  | h :: t -> h + (num_from_reversed_digits_list t) * 10;;

let num_from_digits_list ls = reverse_digits (num_from_reversed_digits_list ls);;

let num_from_digits_list_filter cond ls = num_from_digits_list (List.filter cond ls);;


let rec list_fromto a b step = match (a, b, step) with
  | (_, _, step) when step <= 0 -> invalid_arg "The step must be greater than 0."
  | (a, b, _) when a > b -> []
  | (a, b, _) when a = b -> [a]
  | (a, b, step) -> a :: list_fromto (a + step) b step;;


let list_nth lst n =
  if n < 0 then invalid_arg "n must be positive!"
  else let rec nth_elem ls n acc = match ls with
    | [] -> invalid_arg "n is out of bounds!"
    | h :: t -> if acc = n then h else nth_elem t n (acc + 1)
  in  nth_elem lst n 0;; 