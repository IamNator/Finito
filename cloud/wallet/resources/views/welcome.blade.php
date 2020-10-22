<!DOCTYPE html>
<html lang="en">

<!-- Mirrored from demo.serifly.com/cloudhub/html/home-large-slider.html by HTTrack Website Copier/3.x [XR&CO'2014], Tue, 05 May 2020 00:42:20 GMT -->
<head>
		<meta charset="UTF-8">
		<title>Finito - Payment made easy</title>
		<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
		<!-- Icons -->
		<link rel="apple-touch-icon-precomposed" href="asset-1/img/icons/apple-touch-icon.png">
		<link rel="icon" href="asset-1/img/icons/favicon.ico">
		<!-- Stylesheets -->
		<link rel="stylesheet" href="asset-1/css/fontawesome.min.css">
		<link rel="stylesheet" href="asset-1/css/main.min.css">
	</head>
	<body class="footer-dark">
		<!-- Header -->
		<header id="header" class="header-dynamic header-shadow-scroll">
			<div class="container">
                <a class="logo" href="/">
                    <h1 style="font-size: 40px;font-family: courier,arial,helvetica;">Finito Cloud</h1>
				</a>
				<nav>
					<ul class="nav-primary">
						<li>
                        <a class="button button-secondary" href="{{ route('login') }}">
								<i class="fas fa-lock icon-left"></i>Login
						</a>
                        </li>
                        <li>
                            <a class="button button-secondary" href="{{ route('register') }}">
                                    <i class="fas fa-user icon-left"></i>Register
                            </a>
                        </li>
					</ul>
				</nav>
			</div>
		</header>
		<!-- Notification -->
		<section id="notification" data-dismissible="false" data-title="" data-expires="">
			<div class="container">
				<p>
					This is a beta product, we are working day and night to make it perfect! <i class="fas fa-angle-right icon-right"></i>
				</p>
			</div>
		</section>
		<!-- Content -->
		<section id="content">
			<!-- Content Row -->
			<section class="content-row content-row-color content-row-clouds content-row-full-height">
				<div class="content-slider animate-container-slide" data-nav="true" data-rotation="5">
					<div class="slide" data-title="Cloud Hosting" href="">
						<div class="container text-align-center">
							<header class="content-header content-header-large content-header-uppercase">
								<h1>
									<mark>Finito</mark> Payment like no other
								</h1>
								<p>
									Make secure transfer via finito, offline or online<span class="text-color-secondary">*Beta</span>
								</p>
							</header>
                            <img width="700" src="main.png">
                            {{-- <div align="center">
                                <img src="ps.png" class="img-thumbnail" style="width: 300px">
                            </div> --}}
                        </div>
					</div>
				</div>
				<div class="content-background content-background-light">
					<img src="asset-1/uploads/clouds-light.png" alt="">
				</div>
			</section>
		</section>
		<!-- Scripts -->
		<script src="asset-1/js/jquery.min.js"></script>
		<script src="asset-1/js/headroom.min.js"></script>
		<script src="asset-1/js/js.cookie.min.js"></script>
		<script src="asset-1/js/imagesloaded.min.js"></script>
		<script src="asset-1/js/bricks.min.js"></script>
		<script src="asset-1/js/main.min.js"></script>
	</body>

</html>
