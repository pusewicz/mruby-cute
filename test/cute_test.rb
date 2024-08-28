assert("cf_version_string_linked") do
  assert_match("Cute Framework Version [0-9].[0-9].[0-9] (WIP)", Cute.version_string_linked)
end
