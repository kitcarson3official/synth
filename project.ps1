$project = Split-Path -Path (Get-Location) -Leaf

function build {
  New-Item -Type Directory -Path build -ErrorAction Ignore
    Push-Location build
    cmake -G"Ninja" .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cmake --build .
    Pop-Location
}

function run {
  Push-Location build
    $command = './' + $project
    Invoke-Expression $command
    Pop-Location
}

switch ($args[0]) {
  "build" {
    build
  }

  "run" {
    build
      run $args[1]
  }

  "clean" {
    Remove-Item -Force -Recurse -Path "./build"
  }
  
  default {
    run
  }
}
