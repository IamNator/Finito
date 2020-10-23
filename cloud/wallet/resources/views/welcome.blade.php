<!DOCTYPE html>
<html lang="en">
<head>
    <!--Metas-->
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Finito - Banking like no other</title>

    <!--External Stylesheets css-->

    <!-- Bootstrap -->
<link rel="stylesheet" href="{{ url('')}}/assets/css/bootstrap.min.css">

    <!--Animate -->
    <link rel="stylesheet" href="{{ url('')}}/assets/css/animate.css">

    <!--Slick -->
    <link rel="stylesheet" href="{{ url('')}}/assets/css/slick.css">

    <!-- Magnific Popup-->
    <link rel="stylesheet" href="{{ url('')}}/assets/css/magnific-popup.css">

    <!--Template Stylesheets css-->

    <link rel="stylesheet" href="{{ url('')}}/assets/css/style.css">
    <link rel="stylesheet" href="{{ url('')}}/assets/css/responsive.css">

    <link rel="shortcut icon" href="{{ url('') }}/assets/images/favicon.ico" type="image/x-icon">
    <link rel="icon" href="{{ url('') }}/assets/images/favicon.ico" type="image/x-icon">

    <script src="{{ url('')}}/assets/js/modernizr.js"></script>

    <!--[if lt IE 9]>
  <script src="assets/js/html5shiv.min.js"></script>
  <script src="assets/js/respond.min.js"></script>
<![endif]-->
</head>

<body data-spy="scroll" data-target=".navbar-default" data-offset="100">

    <!-- Page Preloader -->

    <div id="loading-page">
        <div id="loading-center-page">
            <div id="loading-center-absolute">

                <div class="loader"></div>
            </div>
        </div>

    </div>
    <!-- Page Preloader -->

    <!-- Page Content -->

    <div class="warpper clearfix">

        <!--sidebar menu-->

        <a href="#menu-nav" class="menu-nav-trigger">
            Menu
            <span class="menu-nav-icon"></span>

            <svg x="0px" y="0px" width="54px" height="54px" viewBox="0 0 54 54">
                <circle fill="transparent" stroke="#656e79" stroke-width="1" cx="27" cy="27" r="25" stroke-dasharray="157 157" stroke-dashoffset="157"></circle>
            </svg>
        </a>

        <div id="menu-nav" class="menu-nav">
            <div class="menu-navigation-wrapper">
                <div class="menu-half-block">
                    <h2>Menu</h2>

                    <nav>
                        <ul class="menu-primary-nav">
                            <li><a href="#about" class="selected section-scroll">About</a></li>
                            <li><a href="#features" class="section-scroll">Features</a></li>
                        <li><a href="{{ route('login')}}" class="section-scroll">Login</a></li>
                        <li><a href="{{ route('register')}}" class="section-scroll">Register</a></li>

                        </ul>
                    </nav>
                </div>

                <div class="menu-half-block">
                    <address>
                        <ul class="menu-contact-info">
                            <li><a href="mailto:">finito-cloud@gmail.com</a></li>
                            <li>+123456789</li>
                            <li>
                                <span>University Of Ibadan,</span>
                                <span>Ibadan, Oyo State.</span>
                            </li>
                        </ul>
                    </address>
                </div>
            </div>
        </div>
        <!--sidebar menu-->

        <!-- Header -->

        <header class="navbar-header clearfix">

            <nav class="navbar navbar-expand-lg fixed-top">

                <!--container-->
                <div class="container">

                    <!-- Logo -->
                    <a class="navbar-brand" href="#">
                        <h1>Finito</h1>
                    </a>
                    <!-- Logo -->

                    <!-- Get started -->

                    <div class="ml-auto right-nav">
                        <ul>
                            @auth
                            <li>
                                <a href="{{ route('home') }}" class="btn btn-blue">Wallet</a>

                            </li>
                           @else
                            <li>
                                <a href="{{ route('register') }}" class="btn btn-blue">Register</a>

                            </li>
                            <li>
                                <a href="{{ route('login') }}" class="btn btn-blue">Login</a>

                            </li>
                            @endauth
                        </ul>

                    </div>
                    <!-- Get started -->

                </div>

                <!--container-->
            </nav>

        </header>
        <!--Header-->

        <!--Begin Hero Section-->

        <section id="home">

            <div class="container-page  hero">

                <!--container-->

                <div class="container">

                    <div class="row">

                        <div class="col-md-7 col-xs-7 col-sm-7 col-12">

                            <!--text-->

                            <div class="hero-text">

                                <h1>Finito<sup style="font-size: 20px; color: red">BETA</sup></h1>

                                <p> Banking system like no other, make secure transactions online or offline using our app or transfer device.</p>

                                <div class="quote-form">

                                    <input type="text" name="email" class="form-control" placeholder="E-mail Adress">
                                    <button type="submit" class="btn btn-form">Register Now</button>

                                </div>

                                <a href="#" class="icobutton icobutton-arrow btn-secttion"><img src="assets/images/icons/arrow.svg" class="hand" alt=""></a>

                            </div>

                            <!--text-->

                        </div>
                        <div class="col-md-5 col-xs-5 col-sm-5 col-12">

                            <!-- slider image -->

                            <div class="slider-image text-right">

                                <img src="main-2.png" alt="">

                            </div>

                            <!-- slider image -->

                        </div>
                    </div>

                </div>

                <!--container-->
            </div>

        </section>

        <!-- about block colored-->

        <section id="about-p" class="pd-tp-80 pd-bt-40 bg-color-1 about-text">

            <!--container-->

            <div class="container">
                <div class="row">

                    <!--text-->

                    <div class="col-md-5 col-lg-5 col-sm-5 col-12">

                        <h2 align="center">Seemless banking experience like no other.</h2>

                    </div>

                    <!--text-->

                    <!--number block-->

                    <div class="col-md-6 col-lg-6 col-sm-6 offset-md-1 col-12">

                        <div class="row">

                            <div class="col-md-4 col-lg-4 col-sm-4 col-12">

                                <div class="icon-text">

                                    <img src="assets/images/icons/favorites.svg" class="animate-icon" alt="">

                                    <h3>Good Rating</h3>
                                    <span>Reviews</span>

                                </div>

                            </div>

                            <div class="col-md-4 col-lg-4 col-sm-4 col-12">

                                <div class="icon-text">

                                    <img src="assets/images/icons/secure-shield.svg" alt="">

                                    <h3>Secure</h3>
                                    <span>Encrypted Transactions</span>

                                </div>

                            </div>

                            <div class="col-md-4 col-lg-4 col-sm-4 col-12">

                                <div class="icon-text">

                                    <img src="assets/images/icons/headphones.svg" alt="">

                                    <h3>Support</h3>
                                    <span>We are always available</span>

                                </div>

                            </div>

                        </div>

                    </div>

                    <!--number block-->

                </div>

            </div>

            <!--container-->

        </section>

        <!-- about block colored-->

        <!--About app-->

        <section id="about">

            <!--container-->

            <div class="content-text bg-color padd-80">

                <div class="container">
                    <div class="row ">

                        <!-- image-->
                        <div class="col-lg-6 col-md-6 col-12 wow fadeInLeft">

                            <img src="main.png" alt="">

                        </div>

                        <!--image-->

                        <!-- description text-->

                        <div class="col-lg-6 col-md-6 col-12 ">
                        <div align="center">
                            <h2 class="title-h2">Our wallet and device is built</h2>

                            <h3>securely for everyone!</h3>

                            <p class="font-p mg-tp-30 mg-bt-30">
                                The finito device gives you optimum control of transactions even without your mobile device. Make transfer straight from the Finito-Device offline.
                            </p>
                        </div>

                            <ul class="list-text">
                                <li><img src="assets/images/icons/padlock.svg" alt="">

                                    <p> Encrypted data exchange</p>

                                </li>
                                <li><img src="assets/images/icons/credit-card.svg" alt="">
                                    <p> Make payment for services instantly</p>
                                </li>

                                <li><img src="assets/images/icons/investment.svg" alt="">
                                    <p>Have your banking experience in your hands</p>
                                </li>
                            </ul>

                            <div class="actions-btn">

                                {{-- <a href="#" class="btn btn-blue"><img src="assets/images/icons/apple.svg" alt="">Get on IOS</a> --}}

                                <a href="#" class="btn btn-blue"><img src="assets/images/icons/play-store.svg" alt="">Coming soon on Android</a>

                            </div>
                        </div>

                        <!-- description text-->

                    </div>

                </div>

            </div>
            <!--container-->

        </section>






    </div>

    <!-- Footer-->

    <footer class="footer ">
        <div class="container-page ">

            <div class="footer-warpper ">

                <div class="footer-top">
                    <!--container-->
                    <div class="container ">

                        <div class="footer-top  clearfix ">

                           <p align="center">2020 Copyright Finito</p>

                        </div>

                    </div>

                    <!--container-->
                </div>

            </div>
        </div>

    </footer>

    <!--Footer -->
    <!-- jQuery -->
    <script src="assets/js/jquery-3.3.1.min.js"></script>

    <!-- Bootstrap Plugins -->
    <script src="{{ url('')}}/assets/js/bootstrap.min.js"></script>
    <script src="{{ url('')}}/assets/js/jquery.easing.js"></script>
    <script src="{{ url('')}}/assets/js/wow.min.js"></script>
    <script src="{{ url('')}}/assets/js/magnific-popup.min.js"></script>
    <script src="{{ url('')}}/assets/js/jquery.scrollUp.min.js"></script>
    <script src="{{ url('')}}/assets/js/jquery.ajaxchimp.min.js"></script>
    <script src="{{ url('')}}/assets/js/slick.min.js"></script>
    <script src="{{ url('')}}/assets/js/mo.min.js"></script>
    <!-- Main js -->
<script src="{{ url('')}}/assets/js/main.js"></script>
</body>
