@extends('layouts.main')
@section('title')
    Authentication
@endsection
@section('content')
 <!-- App Capsule -->
 <div id="appCapsule">
    <h1 class="" style="font-size: 40px;font-family: courier,arial,helvetica;color: #2b98ef;text-align: center;">Finito Cloud</h1>
    <div class="section mt-2 text-center">
        <h1>Register</h1>
        <h4>Fill the form to register</h4>
    </div>
    <div class="section mb-5 p-2">

        <form method="POST" action="{{ route('register') }}">
            @csrf
            <div class="card">
                <div class="card-body pb-1">
                    <div class="form-group basic">
                        <div class="input-wrapper">
                            <label class="label" for="name">Full Name</label>
                            <input id="text" type="text" class="form-control @error('email') is-invalid @enderror" name="email" value="{{ old('email') }}" required autocomplete="email" autofocus>
                            @error('name')
                                <span class="invalid-feedback" role="alert">
                                    <strong>{{ $message }}</strong>
                                </span>
                            @enderror
                            <i class="clear-input"><ion-icon name="close-circle"></ion-icon></i>
                        </div>
                    </div>

                    <div class="form-group basic">
                        <div class="input-wrapper">
                            <label class="label" for="email1">E-mail</label>
                            <input id="email" type="email" class="form-control @error('email') is-invalid @enderror" name="email" value="{{ old('email') }}" required autocomplete="email" autofocus>
                            @error('email')
                                <span class="invalid-feedback" role="alert">
                                    <strong>{{ $message }}</strong>
                                </span>
                            @enderror
                            <i class="clear-input"><ion-icon name="close-circle"></ion-icon></i>
                        </div>
                    </div>

                    <div class="form-group basic">
                        <div class="input-wrapper">
                            <label class="label" for="password1">Password</label>
                            <input id="password" type="password" class="form-control @error('password') is-invalid @enderror" name="password" required autocomplete="current-password">
                            @error('password')
                                <span class="invalid-feedback" role="alert">
                                    <strong>{{ $message }}</strong>
                                </span>
                            @enderror
                            <i class="clear-input"><ion-icon name="close-circle"></ion-icon></i>
                        </div>
                    </div>
                    <div class="form-group basic">
                        <div class="input-wrapper">
                            <label class="label" for="password-confirm">Confirm Password</label>
                            <input id="password-confirm" type="password" class="form-control" name="password_confirmation" required autocomplete="new-password">
                            <i class="clear-input"><ion-icon name="close-circle"></ion-icon></i>
                        </div>
                    </div>

                </div>
            </div>


            <div class="form-links mt-2">
                <div>
                <a href="{{ route('login') }}">Login Now</a>
                </div>
                <div><a href="{{ route('login') }}" class="text-muted">Forgot Password?</a></div>
            </div>

            <div class="form-button-group  transparent">
                <button type="submit" class="btn btn-primary btn-block btn-lg">Register</button>
            </div>

        </form>
    </div>

</div>
<!-- * App Capsule -->


@endsection
