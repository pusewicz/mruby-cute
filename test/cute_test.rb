assert("cf_version_string_linked") do
  assert_match("Cute Framework Version [0-9].[0-9].[0-9] (WIP)", Cute.cf_version_string_linked)
end
