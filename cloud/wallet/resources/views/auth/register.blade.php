@extends('layouts.main')
@section('title')
    Authentication
@endsection
@section('content')

 <!--breadcrumb area-->
 <section class="breadcrumb-area gradient-overlay" style="background: url('{{ url('') }}/assets/images/banner/3.jpg');">
    <div class="container">
        <div class="row">
            <div class="col-xl-12">
                <div class="site-breadcrumb">
                    <h2>Register Account</h2>
                </div>
            </div>
        </div>
    </div>
</section>
<!--/breadcrumb area-->

<!--Login Section -->
<section class="section-padding blue-bg shaded-bg">
    <div class="container">
        <div class="row justify-content-center">
            <div class="col-xl-8 col-lg-8 col-md-8 col-sm-12 centered">
                <div class="section-title cl-white">
                    <h4>Register account</h4>
                </div>
            </div>
        </div>
        @if ($errors->any())
        <div class="alert alert-danger">
                @foreach ($errors->all() as $error)
                    <li>{{ $error }}</li>
                @endforeach
        </div>
        @endif
        <div class="row justify-content-center">
            <div class="col-xl-5 col-lg-5 col-md-6 col-sm-12">
                <div class="site-form mb-30">
                    <form method="POST" action="{{ route('register') }}">
                        @csrf
                        <div class="row">
                            <div class="col-xl-12 col-lg-12 col-sm-12">
                                <input placeholder="Enter Full Name" id="text" type="text" class="@error('email') is-invalid @enderror" name="name" value="{{ old('name') }}" required autocomplete="name" autofocus>
                            </div>
                            <div class="col-xl-12 col-lg-12 col-sm-12">
                                <input placeholder="Enter Email Address" id="email" type="email" class="@error('email') is-invalid @enderror" name="email" value="{{ old('email') }}" required autocomplete="email" autofocus>
                            </div>
                            <div class="col-xl-12 col-lg-12 col-sm-12">
                                <input placeholder="Enter Password" id="password" type="password" class="form-control @error('password') is-invalid @enderror" name="password" required autocomplete="current-password">
                            </div>
                            <div class="col-xl-12 col-lg-12 col-sm-12">
                                <input placeholder="Confirm Password" id="password-confirm" type="password" class="form-control" name="password_confirmation" required autocomplete="new-password">
                            </div>
                            <div class="col-xl-12 col-lg-12 col-sm-12">
                                <button type="submit" class="bttn-mid btn-fill w-100">Register Account</button>
                            </div>
                            <div class="col-xl-12 col-lg-12 col-sm-12">
                                <div class="extra-links">
                                    <div>
                                        <a href="{{ route('login') }}">Login Now?</a>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </div>
</section><!--/Login Section-->



@endsection
