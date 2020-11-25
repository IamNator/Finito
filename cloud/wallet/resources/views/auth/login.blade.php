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
                        <h2>Login Account</h2>
                    </div>
                </div>
            </div>
        </div>
    </section><!--/breadcrumb area-->

    <!--Login Section -->
    <section class="section-padding blue-bg shaded-bg">
        <div class="container">
            <div class="row justify-content-center">
                <div class="col-xl-8 col-lg-8 col-md-8 col-sm-12 centered">
                    <div class="section-title cl-white">
                        <h4>Login account</h4>
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
                        <form method="POST" action="{{ route('login') }}">
                            @csrf
                            <div class="row">
                                <div class="col-xl-12 col-lg-12 col-sm-12">
                                    <input placeholder="Enter Email Address" id="email" type="email" class="@error('email') is-invalid @enderror" name="email" value="{{ old('email') }}" required autocomplete="email" autofocus>
                                </div>
                                <div class="col-xl-12 col-lg-12 col-sm-12">
                                    <input placeholder="Enter Password" id="password" type="password" class="form-control @error('password') is-invalid @enderror" name="password" required autocomplete="current-password">
                                </div>
                                 <div class="form-check">
                                    <input class="form-check-input" type="checkbox" name="remember" id="remember" {{ old('remember') ? 'checked' : '' }}>
                                    <label class="form-check-label" for="remember">
                                        {{ __('Remember Me') }}
                                    </label>
                                </div>
                                <div class="col-xl-12 col-lg-12 col-sm-12">
                                    <button type="submit" class="bttn-mid btn-fill w-100">Login Account</button>
                                </div>
                                <div class="col-xl-12 col-lg-12 col-sm-12">
                                    <div class="extra-links">
                                        <div>
                                            <a href="{{ route('register') }}">Register Now</a>
                                            </div>
                                            <div><a href="{{ route('login') }}" class="text-muted">Forgot Password?</a></div>
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
