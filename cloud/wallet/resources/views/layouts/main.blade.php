<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">


    <link rel="shortcut icon" href="{{ url('') }}/assets/images/favicon.ico" type="image/x-icon">
    <link rel="icon" href="{{ url('') }}/assets/images/favicon.ico" type="image/x-icon">

    <title>Finito - @yield('title')</title>

    <!-- Bootstrap -->
    <link href="{{ url('') }}/assets/css/bootstrap.min.css" rel="stylesheet">

    <link href="{{ url('') }}/assets/css/font-awesome.min.css" rel="stylesheet">
    <link href="{{ url('') }}/assets/css/magnific-popup.css" rel="stylesheet">
    <link href="{{ url('') }}/assets/css/jquery-ui.css" rel="stylesheet">


    <link href="{{ url('') }}/assets/css/animate.css" rel="stylesheet">
    <link href="{{ url('') }}/assets/css/owl.carousel.min.css" rel="stylesheet">
    <!-- Main css -->
    <link href="{{ url('') }}/assets/css/main.css" rel="stylesheet">

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
    <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>
<body>

    <!-- Preloader -->
    <div class="preloader">
        <div class="lds-roller"><div></div><div></div><div></div><div></div><div></div><div></div><div></div><div></div></div>
    </div><!--/Preloader -->

    <!--Header Area-->
    <header class="header-area blue-bg-2">
        <nav class="navbar navbar-expand-lg main-menu">
            <div class="container-fluid">

                <h1 class="navbar-brand" style="color: white; font-size: 50px">Finito</h1>

                <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                <span class="menu-toggle"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarSupportedContent">
                    <ul class="navbar-nav m-auto">
                        <li class="nav-item"><a class="nav-link" href="{{ route('home') }}">Home</a></li>
                        @auth
                        <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle" href="#" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Menu</a>
                            <ul class="dropdown-menu">
                                <li>
                                    <a class="dropdown-item" href="{{ route('logout') }}"
                                        onclick="event.preventDefault();
                                              document.getElementById('logout-form').submit();">
                                        {{ __('Logout') }}
                                     </a>
                                </li>
                             <form id="logout-form" action="{{ route('logout') }}" method="POST" class="d-none">
                                 @csrf
                             </form>
                            </ul>
                        </li>
                        @endauth
                    </ul>
                </div>
            </div>
        </nav>
    </header><!--/Header Area-->

    @yield('content')
    <!--Footer Area-->
    <footer class="footer-area section-padding-2 blue-bg-2">
        <div class="container">
            <div class="row copyright">
                <div class="col-xl-6 col-sm-6">
                    <div class="copyright-text">
                        <p>Copyright &copy; 2020. All Rights Reserved.</p>
                    </div>
                </div>
            </div>
        </div>
    </footer><!--/Footer Area-->




    <!-- jQuery (necessary for Bootstrap's JavaScript plugins) -->
    <script src="{{ url('') }}/assets/js/jquery-3.2.1.min.js"></script>
    <script src="{{ url('') }}/assets/js/jquery-migrate.js"></script>
    <script src="{{ url('') }}/assets/js/jquery-ui.js"></script>

    <script src="{{ url('') }}/assets/js/popper.js"></script>
    <script src="{{ url('') }}/assets/js/bootstrap.min.js"></script>
    <script src="{{ url('') }}/assets/js/owl.carousel.min.js"></script>

    <script src="{{ url('') }}/assets/js/magnific-popup.min.js"></script>
    <script src="{{ url('') }}/assets/js/imagesloaded.pkgd.min.js"></script>
    <script src="{{ url('') }}/assets/js/isotope.pkgd.min.js"></script>

    <script src="{{ url('') }}/assets/js/waypoints.min.js"></script>
    <script src="{{ url('') }}/assets/js/jquery.counterup.min.js"></script>
    <script src="{{ url('') }}/assets/js/wow.min.js"></script>
    <script src="{{ url('') }}/assets/js/scrollUp.min.js"></script>

    <script src="{{ url('') }}/assets/js/script.js"></script>
</body>

</html>
