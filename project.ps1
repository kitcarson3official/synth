function _Build
{
  Push-Location ./build
  cmake .. -DCMAKE_BUILD_TYPE="Debug"
  cmake --build .
  Pop-Location
}

function _Run
{
  _Build
  if ($LASTEXITCODE -eq 0)
  {
    ./build/synth
  }
}

switch($args[0])
{
  "run"
  {
    _Run 
  }
  default
  {
    _Build
  }
}
